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
#include "map.h"
#include "entity.h"
#include "player.h"

#include "fmod.hpp"
#include "fmod_errors.h"
#include "fmod_common.h"


// Library includes:
#include <cassert>
#include <SDL.h>


#define SERVER_PORT 12345
#define MAX_CONNS 2000
#define SERVER_ADDR "156.62.62.31"

// Static Members:
Game* Game::sm_pInstance = 0;


/////////////
FMOD::System *systemFMOD = NULL;
FMOD::Sound      *sound1, *sound2;
FMOD::Channel    *channel, *channel2;
FMOD_RESULT result;


/////////////
//Liam Shit
RakNet::SystemAddress ServerName;


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

void NetworkThread();


enum GameMessages
{
	NEW_PLAYER = ID_USER_PACKET_ENUM + 1,
	PLAYER_MOVE = ID_USER_PACKET_ENUM + 2,
	PLAYER_LIST = ID_USER_PACKET_ENUM + 3
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
	const int width = 1280;
	const int height = 720;

	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(width, height))
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


	////////////////fmod

	result = FMOD::System_Create(&systemFMOD);      // Create the main system object.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));

		exit(-1);
	}

	result = systemFMOD->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}



	result = systemFMOD->createSound("assets\\opening.wav", FMOD_DEFAULT, 0, &sound1);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = systemFMOD->createSound("assets\\battle.wav", FMOD_DEFAULT, 0, &sound2);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	/////////////////////////////////
	result = systemFMOD->playSound(sound1, 0, false, &channel);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = sound1->setMode(FMOD_LOOP_NORMAL);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}


	

	result = systemFMOD->playSound(sound2, 0, false, &channel2);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = sound2->setMode(FMOD_LOOP_NORMAL);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	channel->setPaused(true);
	channel2->setPaused(true);


	// Ex006.2: Load the player ship sprite.
	// For example: Sprite* pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\playership.png");

	// Ex006.2: Create the player ship instance.

	// Ex006.3: Spawn four rows of 14 alien enemies.

	// Ex006.3: Fill the container with these new enemies.

	// Ex006.2: Load the player ship sprite.
	Sprite* pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\playership.png");


	player = new Player();
	player->Initialise(pPlayerSprite);
	player->SetPositionX(width / 2);
	player->SetPositionY(height / 2);

	////////ryan
	ga_gameState = MAINMENU;
	ga_mainMenu = m_pBackBuffer->CreateSprite("assets\\Menu maybe.png");

	//////////Tom////////////////////////////////////////////////////////////////////////////////////////////
	ga_gameMap = new Map();	
	if (ga_gameMap->getNumItemAt(0,0) == 0){
		ga_currentRoom = m_pBackBuffer->CreateSprite("assets\\AllDoorsClosedRoom1280.png");
	}
	else{
		ga_currentRoom = m_pBackBuffer->CreateSprite("assets\\playership.png");
	}

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

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	if (ga_gameState == MAINMENU){
		channel->setPaused(false);
		channel2->setPaused(true);
	}
	else {
		if (ga_gameState == RUNNING){
			channel->setPaused(true);
			channel2->setPaused(false);
		}
	}

	for (it_players iterator = playerList.begin(); iterator != playerList.end(); iterator++)
	{
		Player* e = (Player*)iterator->second;
		e->Process(deltaTime);
	}

	// Update the game world simulation:

	// Ex003.5: Process each alien enemy in the container.

	// Ex006.4: Process each bullet in the container.

	// Ex006.2: Update player...

	// Ex006.4: Check for bullet vs alien enemy collisions...
	// Ex006.4: For each bullet
	// Ex006.4: For each alien enemy
	// Ex006.4: Check collision between two entities.
	// Ex006.4: If collided, destory both and spawn explosion.

	// Ex006.4: Remove any dead bullets from the container...

	// Ex006.4: Remove any dead enemy aliens from the container...

	// Ex006.4: Remove any dead explosions from the container...
}

void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	// Ex006.3: Draw all enemy aliens in container...

	// Ex006.4: Draw all bullets in container...

	////testing
	if (ga_gameState == MAINMENU){
		ga_mainMenu->Draw(backBuffer);
	}
	else if (ga_gameState == RUNNING){
		ga_currentRoom->Draw(backBuffer);
		for (it_players iterator = playerList.begin(); iterator != playerList.end(); iterator++)
		{
			Player* e = (Player*)iterator->second;
			e->Draw(backBuffer);
		}
	}

	// Ex006.2: Draw the player ship...

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

// Ex006.2: Add the method to tell the player ship to move right...

// Ex006.4: Space a Bullet in game.
void 
Game::FireSpaceShipBullet()
{
	// Ex006.4: Load the player bullet sprite.      

	// Ex006.4: Create a new bullet object.

	// Ex006.4: Set the bullets vertical velocity.

	// Ex006.4: Add the new bullet to the bullet container.
}

// Ex006.3: Spawn a Enemy in game.
void 
Game::SpawnEnemy(int x, int y)
{
	// Ex006.3: Load the alien enemy sprite file.

	// Ex006.3: Create a new Enemy object. 

	// Ex006.3: Add the new Enemy to the enemy container.
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
					int i = 0;
					for (it_players iterator = playerList.begin(); iterator != playerList.end(); iterator++)
					{

						// std::string s = std::to_string(i);
						playerList[1] = pl;

					}

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

					peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);



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
					Game& game = Game::GetGame();
					//game.MoveSpaceShipRight(y);
					BackBuffer* backBuffer = game.CallBackBuffer();
					Sprite* pPlayerSprite = backBuffer->CreateSprite("assets\\playership.png");
					Player* pl = new Player();
					pl->Initialise(pPlayerSprite);
					pl->SetPositionX(x);
					pl->SetPositionY(y);

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

					//playerList.at(playerID)->SetHorizontalVelocity(speed);

					//Entity* e = playerList.find("1")->second;
					//e->SetHorizontalVelocity(speed);
					//RakNet::BitStream bsIn(packet->data, packet->length, false);
					//bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					//bsIn.Read(playerID);
					//bsIn.Read(speed);

					//for (it_players iterator = playerList.begin(); iterator != playerList.end(); iterator++){
					//	if (iterator->first == playerID)
					//{
					//	Entity* e = iterator->second;
					//	e->SetHorizontalVelocity(speed);
					//	}
					//}

					//	Entity* e = playerList.find(playerID)->second;

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