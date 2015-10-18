// 717310 C++ SDL Framework

// This includes:
#include "game.h"


#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"
#include "RakPeerInterface.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <map>
#include <stack>
#include <deque>
#include <vector>

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"

#include "gameMap.h"
#include "entity.h"
#include "player.h"
#include "fmodhelper.h"

// Library includes:
#include <cassert>
#include <SDL.h>


#define SERVER_PORT 12345
#define MAX_CONNS 2000
#define SERVER_ADDR "127.0.0.1"

// Static Members:
Game* Game::sm_pInstance = 0;


//Liam Shit
RakNet::SystemAddress ServerName;

float serverCounter = 0.0;


RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
RakNet::Packet *packet;
bool isServer = false;
bool sending = true;
char str[512];
bool isRunning;
std::map<int, RakNet::SystemAddress> netClients;
typedef std::map<int, RakNet::SystemAddress>::iterator it_sysaddr;
std::map<int, Player*> playerList;
typedef std::map<int, Player*>::iterator it_players;
int clientID;
void NetworkThread();


//////////////////////////////////////////////////////////////////////////
//needs to be done
//
//
//Move fmod into methods so it dont look so ugly
//rework them maps
//
//
//
//
//////////////////////////////////////////////////////////////////////



enum GameMessages
{
	NEW_PLAYER = ID_USER_PACKET_ENUM + 1,
	PLAYER_MOVE = ID_USER_PACKET_ENUM + 2,
	PLAYER_LIST = ID_USER_PACKET_ENUM + 3,
	NET_UPDATE = ID_USER_PACKET_ENUM + 4,
	PLAYER_DISCONNECT = ID_USER_PACKET_ENUM + 5,
	CLIENT_ID = ID_USER_PACKET_ENUM + 6
};

Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{ 
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

Game&
Game::GetGame()
{
	return *sm_pInstance;
}

void 
Game::DestroyInstance()
{
	delete sm_pInstance; 
	sm_pInstance = 0;
}

Game::Game()
: m_pBackBuffer(0)
, m_pInputHandler(0)
, m_looping(true)
, m_executionTime(0)
, m_elapsedSeconds(0)
, m_frameCount(0)
, m_FPS(0)
, m_numUpdates(0)
, m_lastTime(0)
, m_lag(0)
{
	
}

Game::~Game()
{
	delete m_pBackBuffer;
	m_pBackBuffer = 0;
}

bool 
Game::Initialise()
{
	
	screenWidth = 1280;
	screenHeight = 720;

	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(screenWidth, screenHeight))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	//FMOD CLASS TOM MADE
	ga_fmodhelp = new FMODHelper();
	ga_fmodhelp->playBackgroundMusic(1);

	Sprite* pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\playership.png");


	player = new Player();
	player->Initialise(pPlayerSprite);
	player->SetPositionX(screenWidth / 2);
	player->SetPositionY(screenHeight / 2);

	////////ryan
	ga_gameState = MAINMENU;
	ga_mainMenu = m_pBackBuffer->CreateSprite("assets\\Menu maybe.png");

	//////////Tom///////////////////////////////////
	ga_gameMap = new GameMap();	
	ga_gameMap->parseFile();

	///////////////////////////////////////////////
	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;

	return (true);
}

bool 
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);
	m_pInputHandler->ProcessInput(*this);
	
	if (m_looping)
	{
		int current = SDL_GetTicks();
		float deltaTime = (current - m_lastTime) / 1000.0f;
		m_lastTime = current;

		m_executionTime += deltaTime;

		m_lag += deltaTime;

		while (m_lag >= stepSize)
		{
			Process(stepSize);

			m_lag -= stepSize;

			++m_numUpdates;
		}
		
		Draw(*m_pBackBuffer);
	}

	SDL_Delay(1);

	return (m_looping);
}

void 
Game::Process(float deltaTime)
{
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;
	if (isServer)
	{
		serverCounter += deltaTime;
		if (serverCounter > 0.1)
		{
			RakNet::BitStream bsOut;
			bsOut.Write((RakNet::MessageID)NET_UPDATE);
			int plSize = playerList.size();
			bsOut.Write(plSize);

			for (it_players iterator = playerList.begin(); iterator != playerList.end(); iterator++)
			{
				Player* e = iterator->second;

				bsOut.Write(e->GetPositionX());
				bsOut.Write(e->GetPositionY());
			}

			for (it_sysaddr iterator = netClients.begin(); iterator != netClients.end(); iterator++)
			{
				peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, iterator->second, false);
			}
			serverCounter = 0;
		}
	}

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	for (it_players iterator = playerList.begin(); iterator != playerList.end(); iterator++)
	{
		Player* e = (Player*)iterator->second;
		e->Process(deltaTime);
	}

	
	updateCamera();

}

void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	
	if (ga_gameState == MAINMENU){
		ga_mainMenu->Draw(backBuffer);
	}
	else if (ga_gameState == RUNNING){

		ga_gameMap->draw(backBuffer);


		for (it_players iterator = playerList.begin(); iterator != playerList.end(); iterator++)
		{
			Player* e = (Player*)iterator->second;
			e->Draw(backBuffer);
		}
	}

	

	backBuffer.Present();
}

void 
Game::Quit()
{
	m_looping = false;
}

void
Game::MoveSpaceShipHor(float speed)
{
	if (isServer)
	{
		for (it_sysaddr iterator = netClients.begin(); iterator != netClients.end(); iterator++){
			RakNet::BitStream bsOut;
			bsOut.Write((RakNet::MessageID)PLAYER_MOVE);
			bsOut.Write(0);
			bsOut.Write(0);
			bsOut.Write(speed);
			peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, iterator->second, false);
		}

		playerList.at(0)->SetHorizontalVelocity(speed);
	}
	// Ex006.2: Tell the player ship to move left.  
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)PLAYER_MOVE);
	//float test = 100.0;
	bsOut.Write(0);
	bsOut.Write(speed);
	peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, ServerName, false);
}

void
Game::MoveSpaceShipVert(float speed)
{
	if (isServer)
	{
		for (it_sysaddr iterator = netClients.begin(); iterator != netClients.end(); iterator++){
			RakNet::BitStream bsOut;
			bsOut.Write((RakNet::MessageID)PLAYER_MOVE);
			bsOut.Write(0);
			bsOut.Write(1);
			bsOut.Write(speed);
			peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, iterator->second, false);
		}
			playerList.at(0)->SetVerticalVelocity(speed);
	}

	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)PLAYER_MOVE);
	//float test = 100.0;
	bsOut.Write(1);
	bsOut.Write(speed);
	peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, ServerName, false);
}


void 
Game::FireSpaceShipBullet()
{
	
}

void 
Game::SpawnEnemy(int x, int y)
{
	
}


void
Game::initiateServer()
{
	RakNet::SocketDescriptor sd(SERVER_PORT, 0);
	peer->SetMaximumIncomingConnections(MAX_CONNS);
	peer->Startup(MAX_CONNS, &sd, 1);
	isServer = true;
	printf("Server is ready to receive connections.\n");

	playerList[0] = player;

	std::thread nt(NetworkThread);

	nt.detach();
}

void
Game::disconnectClient()
{
	//for (it_players iterator = playerList.begin(); iterator != playerList.end(); iterator++)
	//{
		//if (clientID == iterator->first)
		//{
		//	playerList.erase(iterator->first);
		//}
		//iterator->second->SetPositionX(x);
		//iterator->second->SetPositionY(y);
	//}
}

void
Game::initiateClient()
{
	if (!isServer){
		RakNet::SocketDescriptor sd;
		peer->Startup(1, &RakNet::SocketDescriptor(), 1);
		isServer = false;
		printf("Client is connecting to %s:%d\n", SERVER_ADDR, SERVER_PORT);
		peer->Connect(SERVER_ADDR, SERVER_PORT, 0, 0);

		std::thread nt(NetworkThread);

		nt.detach();
	}
}

/////// Liam
void
NetworkThread()
{


	isRunning = true;
	while (isRunning){
		if (isServer){
			for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
			{
				switch (packet->data[0])
				{
				case ID_NEW_INCOMING_CONNECTION:
				{
									netClients[netClients.size() + 1] = packet->systemAddress;
									printf("A remote system has successfully connected.\n");
				}
					break;
				case ID_DISCONNECTION_NOTIFICATION:
					printf("A remote system has disconnected.\n");
					break;
				case ID_CONNECTION_LOST:
					printf("A remote system lost the connection.\n");
					break;
				case NEW_PLAYER:
				{
								   float x, y;
								   RakNet::BitStream bsIn(packet->data, packet->length, false);
								   bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
								   bsIn.Read(x);
								   bsIn.Read(y);
								   Game& game = Game::GetGame();
								   //game.MoveSpaceShipRight(y);
								   BackBuffer* backBuffer = game.CallBackBuffer();
								   Sprite* pPlayerSprite = backBuffer->CreateSprite("assets\\playership.png");
								   Player* pl = new Player();
								   pl->Initialise(pPlayerSprite);
								   pl->SetPositionX(x);
								   pl->SetPositionY(y);

								   int i = playerList.size();
								   playerList[i] = pl;


								   RakNet::BitStream IDreturn;
								   IDreturn.Write((RakNet::MessageID)PLAYER_LIST);
								   IDreturn.Write(i);
								   peer->Send(&IDreturn, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

								   RakNet::BitStream bsOut;
								   bsOut.Write((RakNet::MessageID)PLAYER_LIST);
								   int plSize = playerList.size();
								   bsOut.Write(plSize);

								   for (it_players iterator = playerList.begin(); iterator != playerList.end(); iterator++)
								   {
									   Player* e = iterator->second;

									   bsOut.Write(e->GetPositionX());
									   bsOut.Write(e->GetPositionY());
								   }
								   for (it_sysaddr iterator = netClients.begin(); iterator != netClients.end(); iterator++)
								   {
									   peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, iterator->second, false);
								   }
				}
					break;
				case PLAYER_MOVE:
				{
									int dirCheck;
									float speed;
									RakNet::BitStream bsIn(packet->data, packet->length, false);
									bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
									bsIn.Read(dirCheck);
									bsIn.Read(speed);
									int i;

									for (it_sysaddr iterator = netClients.begin(); iterator != netClients.end(); iterator++){
										if (packet->systemAddress == iterator->second)
										{
											i = iterator->first;
										}
									}

									for (it_sysaddr iterator = netClients.begin(); iterator != netClients.end(); iterator++){
										RakNet::BitStream bsOut;
										bsOut.Write((RakNet::MessageID)PLAYER_MOVE);
										bsOut.Write(i);
										bsOut.Write(dirCheck);
										bsOut.Write(speed);
										peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, iterator->second, false);
									}


									if (dirCheck == 0)
										playerList.at(i)->SetHorizontalVelocity(speed);
									//	e->SetHorizontalVelocity(speed);
									else if (dirCheck == 1)
										playerList.at(i)->SetVerticalVelocity(speed);
				}
					break;
				case NET_UPDATE:
				{

				}
					break;
				}
			}
		}
		else
		{

			for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
			{
				switch (packet->data[0])
				{
				case ID_CONNECTION_REQUEST_ACCEPTED:
				{
													   printf("The connection to the server has been accepted.\n");
													   ServerName = packet->systemAddress;
													   RakNet::BitStream bsOut;
													   float x, y;
													   x = 300.0;
													   y = 200.0;


													   bsOut.Write((RakNet::MessageID)NEW_PLAYER);
													   bsOut.Write(x);
													   bsOut.Write(y);
													   peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
				}
					break;
				case PLAYER_LIST:
				{
									int plSize;
									RakNet::BitStream bsIn(packet->data, packet->length, false);
									bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
									bsIn.Read(plSize);
									for (int i = 0; i < plSize; i++)
									{
										Game& game = Game::GetGame();
										//game.MoveSpaceShipRight(y);
										BackBuffer* backBuffer = game.CallBackBuffer();
										Sprite* pPlayerSprite = backBuffer->CreateSprite("assets\\playership.png");
										Player* pl = new Player();
										pl->Initialise(pPlayerSprite);
										float x, y;
										bsIn.Read(x);
										bsIn.Read(y);

										pl->SetPositionX(x);
										pl->SetPositionY(y);

										playerList[i] = pl;
									}



				}
					break;
				case PLAYER_MOVE:
				{

									int i;
									int dirCheck;
									float speed;
									RakNet::BitStream bsIn(packet->data, packet->length, false);
									bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
									bsIn.Read(i);
									bsIn.Read(dirCheck);
									bsIn.Read(speed);

									//playerID = rs.C_String();
									if (dirCheck == 0)
										playerList.at(i)->SetHorizontalVelocity(speed);
									else if (dirCheck == 1)
										playerList.at(i)->SetVerticalVelocity(speed);



				}
					break;
				case NET_UPDATE:
				{
								   int plSize;

								   RakNet::BitStream bsIn(packet->data, packet->length, false);
								   bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
								   bsIn.Read(plSize);

								   for (it_players iterator = playerList.begin(); iterator != playerList.end(); iterator++)
								   {
									   float x, y;
									   bsIn.Read(x);
									   bsIn.Read(y);

									   iterator->second->SetPositionX(x);
									   iterator->second->SetPositionY(y);
								   }


				}
					break;
				case CLIENT_ID:
				{

								  RakNet::BitStream bsIn(packet->data, packet->length, false);
								  bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
								  bsIn.Read(clientID);
				}
					break;
				}

			}


		}
		Sleep(10);
	}
	RakNet::RakPeerInterface::DestroyInstance(peer);
}

BackBuffer*
Game::CallBackBuffer()
{
	return m_pBackBuffer;
}


void
Game::updateCamera(){

	float charPosX = player->GetPositionX();
	float charPosY = player->GetPositionY();

	int roomX = player->getCurrentRoomX();
	int roomY = player->getCurrentRoomY();

	m_pBackBuffer->SetCameraX(roomX*screenWidth);
	m_pBackBuffer->SetCameraY(roomY*screenHeight);

}