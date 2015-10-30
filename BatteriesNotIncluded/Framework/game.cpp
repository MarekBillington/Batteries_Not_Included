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
#include "animatedsprite.h"
#include "bullet.h"
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
bool serverInitiated = false;
bool sending = true;
char str[512];
bool isRunning;
float volumeSlide = 1.0f;
char* name = "NAME";
std::string clientName = "";
char* serverAdd = "IP";
std::string serverIP = "";

std::map<int, char*> clientNames;
typedef std::map<int, char[]>::iterator it_names;
std::map<int, RakNet::SystemAddress> netClients;
typedef std::map<int, RakNet::SystemAddress>::iterator it_sysaddr;
std::map<int, Player*> playerList;
typedef std::map<int, Player*>::iterator it_players;
std::map<int, Sprite*> playerL2TextList;
typedef std::map<int, Sprite*>::iterator it_L2Text;
int clientID;
void NetworkThread();


Bullet* one_bul[20];
Bullet* two_bul[20];
Bullet* three_bul[20];
Bullet* four_bul[20];

//James Shit
bool hudCreated = false;
bool playerCreated = false;


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
	CLIENT_ID = ID_USER_PACKET_ENUM + 6,
	CLIENT_END = ID_USER_PACKET_ENUM + 7,
	LOBBY_NEW_PLAYER = ID_USER_PACKET_ENUM + 8,
	PLAYER_SHOOT = ID_USER_PACKET_ENUM + 9
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

void
Game::Reset()
{
	isRunning = false;
	serverInitiated = false;
	screenWidth = 1280;
	screenHeight = 720;
	

	//FMOD CLASS TOM MADE
	ga_fmodhelp->playBackgroundMusic(1);

	SDL_Color color = { 0xFF, 0x99, 0x00, 0xFF };





	////////ryan
	ga_gameState = MAINMENU;

	ga_lobbyHost->SetX(screenWidth / 2 - 300);
	ga_lobbyHost->SetY(screenHeight / 2 - 200);


	ga_hostText1 = m_pBackBuffer->CreateText("Type the IP you want to join: ", color, "assets\\dkjalebi.otf", 42);
	ga_hostText1->SetX(450);
	ga_hostText1->SetY(250);

	ga_hostText2 = m_pBackBuffer->CreateText(serverAdd, color, "assets\\dkjalebi.otf", 42);
	ga_hostText2->SetX(550);
	ga_hostText2->SetY(350);

	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;

	ga_hud = 0;
}

bool 
Game::Initialise()
{
	
	screenWidth = 1280;
	screenHeight = 720;

	secondsToBoss = 0;
	minutesToBoss = 10;

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

	SDL_Color color = { 0xFF, 0x99, 0x00, 0xFF };
	


	

	////////ryan
	ga_gameState = MAINMENU;
	ga_mainMenu = m_pBackBuffer->CreateSprite("assets\\Menu maybe.png");
	ga_lobbyChoose = m_pBackBuffer->CreateSprite("assets\\lobbychoose.png");
	ga_lobbyWait = m_pBackBuffer->CreateSprite("assets\\lobby2.png");
	ga_lobbyHost = m_pBackBuffer->CreateSprite("assets\\ipshow.png");
	ga_nameBox = m_pBackBuffer->CreateSprite("assets\\ipshow.png");
	ga_options = m_pBackBuffer->CreateSprite("assets\\options.png");
	ga_volumeSlider = m_pBackBuffer->CreateSprite("assets\\volumeAdjuster.png");
	ga_volumeSlider->SetX(900);
	ga_volumeSlider->SetY(495);

	ga_nameBox->SetX(screenWidth / 2 - 400);
	ga_nameBox->SetY(screenHeight / 2 - 200);

	ga_nameChange1 = m_pBackBuffer->CreateText("Type in your new name", color, "assets\\dkjalebi.otf", 42);
	ga_nameChange1->SetX(400);
	ga_nameChange1->SetY(250);

	ga_nameChange2 = m_pBackBuffer->CreateText(name, color, "assets\\dkjalebi.otf", 42);
	ga_nameChange2->SetX(500);
	ga_nameChange2->SetY(350);

	ga_lobbyHost->SetX(screenWidth / 2 - 300);
	ga_lobbyHost->SetY(screenHeight / 2 - 200);


	ga_hostText1 = m_pBackBuffer->CreateText("Type the IP you want to join: ", color, "assets\\dkjalebi.otf", 42);
	ga_hostText1->SetX(450);
	ga_hostText1->SetY(250);

	ga_hostText2 = m_pBackBuffer->CreateText(serverAdd, color, "assets\\dkjalebi.otf", 42);
	ga_hostText2->SetX(550);
	ga_hostText2->SetY(350);

	//////////Tom///////////////////////////////////
	ga_gameMap = new GameMap(m_pBackBuffer);	
	ga_gameMap->parseFile();

	///////////////////////////////////////////////
	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;

	ga_hud = 0;

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
	if (hudCreated){
		ga_hud = new Hud(playerList.at(clientID));
		hudCreated = false;
		if (playerList.size() > 1) {
			playerList.at(1)->SetPositionX(640);
			playerList.at(1)->SetPositionY((8 * 720) + 360);
		}
		if (playerList.size() > 2) {
			playerList.at(2)->SetPositionX((8 * 1280)+ 640);
			playerList.at(2)->SetPositionY((8 * 720)+360);
		}
		if (playerList.size() > 3) {
			playerList.at(3)->SetPositionX((8 * 1280) + 640);
		}
	}
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;
	if (isServer)
	{
		serverCounter += deltaTime;
		if (serverCounter > 0.01666666666666666)
		{
			RakNet::BitStream bsOut;
			bsOut.Write((RakNet::MessageID)NET_UPDATE);
			int plSize = playerList.size();
			bsOut.Write(plSize);

			for (it_players iterator = playerList.begin(); iterator != playerList.end(); iterator++)
			{
				Player* e = (Player*)iterator->second;
				
				/*if (ga_gameState == RUNNING){
					ga_gameMap->getRoomAt(e->getCurrentRoomX(), e->getCurrentRoomY())->IsCollidingWith(*e);
				}*/
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
		//Boss Timer
		if (ga_gameState == RUNNING){
			if (secondsToBoss == 0 && minutesToBoss > 0){
				minutesToBoss--;
				secondsToBoss = 59;
			}
			else if (secondsToBoss > 0){
				secondsToBoss--;
			}
			//Move to Boss Room
			if (minutesToBoss == 0 && secondsToBoss == 0 && bossTime == false){
				playerList.at(clientID)->SetPositionX((4 * 1280) + 200 + (clientID*50));
				playerList.at(clientID)->SetPositionY((3 * 720) + 460);
				bossTime = true;
				ga_gameMap->getRoomAt(4, 3)->ro_Locked = true;
			}
		}
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	for (it_players iterator = playerList.begin(); iterator != playerList.end(); iterator++)
	{
		Player* e = (Player*)iterator->second;
		ga_gameMap->getRoomAt(e->getCurrentRoomX(), e->getCurrentRoomY())->IsCollidingWith(*e);
		e->Process(deltaTime);
		//basic Respawn(
		if (e->getHealth() <= 0){
			e->setHealth(1000);
			e->pl_deathCount++;
			if (playerList.size() > 0){
				int tempX;
				int tempY;
				if (!bossTime){
					tempX = 640;
					tempY = 320;
				}
				else {
					tempX = (4 * 1280) + 200 + (0 * 50);
					tempY = (3 * 720) + 460;
				}
				if (e == playerList[0]){
					playerList.at(0)->SetPositionX(tempX);
					playerList.at(0)->SetPositionY(tempY);
				}
			}
			if (playerList.size() > 1) {
				if (e == playerList[1]){
					int tempX;
					int tempY;
					if (!bossTime){
						tempX = 640;
						tempY = (8 * 720) + 360;
					}
					else {
						tempX = (4 * 1280) + 200 + (1 * 50);
						tempY = (3 * 720) + 460;
					}
					if (e == playerList[1]){
						playerList.at(1)->SetPositionX(tempX);
						playerList.at(1)->SetPositionY(tempY);
					}
				}
			}
			if (playerList.size() > 2) {
				if (e == playerList[2]){
					int tempX;
					int tempY;
					if (!bossTime){
						tempX = (8 * 1280) + 640;
						tempY = (8 * 720) + 360;
					}
					else {
						tempX = (4 * 1280) + 200 + (2 * 50);
						tempY = (3 * 720) + 460;
					}
					if (e == playerList[2]){
						playerList.at(2)->SetPositionX(tempX);
						playerList.at(2)->SetPositionY(tempY);
					}
				}
			}
			if (playerList.size() > 3) {
				if (e == playerList[3]){
					int tempX;
					int tempY;
					if (!bossTime){
						tempX = (8 * 1280) + 640;
						tempY = 360;
					}
					else {
						tempX = (4 * 1280) + 200 + (3 * 50);
						tempY = (3 * 720) + 460;
					}
					if (e == playerList[3]){
						playerList.at(3)->SetPositionX(tempX);
						playerList.at(3)->SetPositionY(tempY);
					}
				}
			}
			
		}
		for (it_players iterator1 = playerList.begin(); iterator1 != playerList.end(); iterator1++)
		{
			Player* randySavage = (Player*)iterator1->second;
			if ((e->getCurrentRoomX() != randySavage->getCurrentRoomX() || e->getCurrentRoomY() != randySavage->getCurrentRoomY()) && iterator->first != iterator1->first){
				ga_gameMap->getRoomAt(randySavage->getCurrentRoomX(), randySavage->getCurrentRoomY())->ro_Locked = false;
			}

		}
		for (int i = 0; i < e->pl_bulletContainer.size(); i++)
		{
			Bullet* e_bullet = e->pl_bulletContainer.at(i);
			int stuff = clientID;
			if (/*(e_bullet->getClient() != clientID) &&*/ e_bullet->IsCollidingWith(*e))
			{
					e->setHealth(e->getHealth() - 50);
					e_bullet->SetDead(true);
			}
			if ((e_bullet->getCurrentRoomX() != e->getCurrentRoomX()) || (e_bullet->getCurrentRoomY() != e->getCurrentRoomY()))
			{
				e_bullet->SetDead(true);
			}
			/*if (((e->GetPositionX() + 1280) > e_bullet->GetPositionX() || (e->GetPositionX() + 1280) < e_bullet->GetPositionX())
				|| ((e->GetPositionY() + 720) > e_bullet->GetPositionY() || (e->GetPositionY() + 720) < e_bullet->GetPositionY()))
			{
				e_bullet->SetDead(true);
			}*/
			if (e_bullet->IsDead())
			{
				
				e->pl_bulletContainer.erase(e->pl_bulletContainer.begin() + i);
				delete e_bullet;
			}

			
			e_bullet->Process(deltaTime);
			//e_bullet->SetDead(true);
			
		}
	}
			
	if (playerList.size() > 0){
		if (playerList.size() > 1){
			if (playerList[0]->getCurrentRoomX() == playerList[1]->getCurrentRoomX() && playerList[0]->getCurrentRoomY() == playerList[1]->getCurrentRoomY()){
				ga_gameMap->getRoomAt(playerList[0]->getCurrentRoomX(), playerList[0]->getCurrentRoomY())->ro_Locked = true;
			}
			if (playerList.size() > 2){
				if (playerList[2]->getCurrentRoomX() == playerList[1]->getCurrentRoomX() && playerList[2]->getCurrentRoomY() == playerList[1]->getCurrentRoomY()){
					ga_gameMap->getRoomAt(playerList[2]->getCurrentRoomX(), playerList[2]->getCurrentRoomY())->ro_Locked = true;
				}
				if (playerList[0]->getCurrentRoomX() == playerList[2]->getCurrentRoomX() && playerList[0]->getCurrentRoomY() == playerList[2]->getCurrentRoomY()){
					ga_gameMap->getRoomAt(playerList[0]->getCurrentRoomX(), playerList[0]->getCurrentRoomY())->ro_Locked = true;
				}
				if (playerList.size() > 3){
					if (playerList[3]->getCurrentRoomX() == playerList[1]->getCurrentRoomX() && playerList[3]->getCurrentRoomY() == playerList[1]->getCurrentRoomY()){
						ga_gameMap->getRoomAt(playerList[3]->getCurrentRoomX(), playerList[3]->getCurrentRoomY())->ro_Locked = true;
					}
					if (playerList[0]->getCurrentRoomX() == playerList[3]->getCurrentRoomX() && playerList[0]->getCurrentRoomY() == playerList[3]->getCurrentRoomY()){
						ga_gameMap->getRoomAt(playerList[0]->getCurrentRoomX(), playerList[0]->getCurrentRoomY())->ro_Locked = true;
					}
					if (playerList[2]->getCurrentRoomX() == playerList[3]->getCurrentRoomX() && playerList[2]->getCurrentRoomY() == playerList[3]->getCurrentRoomY()){
						ga_gameMap->getRoomAt(playerList[2]->getCurrentRoomX(), playerList[2]->getCurrentRoomY())->ro_Locked = true;
					}
				}
			}
		}
	}

	ga_fmodhelp->update();
	
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
	else if (ga_gameState == OPTIONS)
	{
		ga_options->Draw(backBuffer);
		ga_volumeSlider->Draw(backBuffer);
	}
	else if (ga_gameState == OPTIONS_NAME)
	{
		ga_options->Draw(backBuffer);
		ga_nameBox->Draw(backBuffer);
		ga_nameChange1->Draw(backBuffer);
		ga_nameChange2->Draw(backBuffer);
	}
	else if (ga_gameState == LOBBY_CHOOSE)
	{
		ga_lobbyChoose->Draw(backBuffer);
	}
	
	else if (ga_gameState == LOBBY_JOIN)
	{
		ga_lobbyChoose->Draw(backBuffer);
		ga_lobbyHost->Draw(backBuffer);
		ga_hostText1->Draw(backBuffer);
		ga_hostText2->Draw(backBuffer);
	}
	else if (ga_gameState == LOBBY)
	{
		ga_lobbyWait->Draw(backBuffer);
		for (it_L2Text iterator = playerL2TextList.begin(); iterator != playerL2TextList.end(); iterator++)
		{
			iterator->second->Draw(backBuffer);
		}
		if (isServer){
			ga_hostText1->Draw(backBuffer);
			ga_hostText2->Draw(backBuffer);
		}
	}
	else if (ga_gameState == RUNNING){

		ga_gameMap->draw(backBuffer);


		for (it_players iterator = playerList.begin(); iterator != playerList.end(); iterator++)
		{
			Player* e = iterator->second;
			e->Draw(backBuffer, clientNames[clientID]);

			if (e->pl_bulletContainer.size() != 0){
				for each(Bullet* bullet in e->pl_bulletContainer)
				{
					if (!bullet->IsDead())
					{
						bullet->Draw(backBuffer);
					}
				}
			}
		}
		

		if (playerCreated){
			//Probably a bad way to do this but im tired
			RoomType type = ga_gameMap->getRoomAt(playerList.at(clientID)->getCurrentRoomX(), playerList.at(clientID)->getCurrentRoomY())->getRoomType();
			if (type == fourDoors){
				ga_gameMap->BottomWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->BottomWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->BottomWallDoor->Draw(backBuffer);

				ga_gameMap->TopWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->TopWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->TopWallDoor->Draw(backBuffer);

				ga_gameMap->RightWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->RightWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->RightWallDoor->Draw(backBuffer);

				ga_gameMap->LeftWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->LeftWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->LeftWallDoor->Draw(backBuffer);

			}
			else if (type == threeDoorsTopWall){
				ga_gameMap->BottomWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->BottomWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->BottomWallDoor->Draw(backBuffer);

				ga_gameMap->TopWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->TopWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->TopWallNoDoor->Draw(backBuffer);

				ga_gameMap->RightWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->RightWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->RightWallDoor->Draw(backBuffer);

				ga_gameMap->LeftWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->LeftWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->LeftWallDoor->Draw(backBuffer);
			}
			else if (type == threeDoorsBottomWall){
				ga_gameMap->BottomWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->BottomWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->BottomWallNoDoor->Draw(backBuffer);

				ga_gameMap->TopWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->TopWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->TopWallDoor->Draw(backBuffer);

				ga_gameMap->RightWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->RightWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->RightWallDoor->Draw(backBuffer);

				ga_gameMap->LeftWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->LeftWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->LeftWallDoor->Draw(backBuffer);
			}
			else if (type == threeDoorsLeftWall){
				ga_gameMap->BottomWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->BottomWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->BottomWallDoor->Draw(backBuffer);

				ga_gameMap->TopWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->TopWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->TopWallDoor->Draw(backBuffer);

				ga_gameMap->RightWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->RightWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->RightWallDoor->Draw(backBuffer);

				ga_gameMap->LeftWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->LeftWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->LeftWallNoDoor->Draw(backBuffer);
			}
			else if (type == threeDoorsRightWall){
				ga_gameMap->BottomWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->BottomWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->BottomWallDoor->Draw(backBuffer);

				ga_gameMap->TopWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->TopWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->TopWallDoor->Draw(backBuffer);

				ga_gameMap->RightWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->RightWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->RightWallNoDoor->Draw(backBuffer);

				ga_gameMap->LeftWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->LeftWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
				ga_gameMap->LeftWallDoor->Draw(backBuffer);
			}
			else if (type == twoDoorsTopLeftWalls){
				ga_gameMap->BottomWallDoor->Draw(backBuffer);
				ga_gameMap->BottomWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->BottomWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->TopWallNoDoor->Draw(backBuffer);
				ga_gameMap->TopWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->TopWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->RightWallDoor->Draw(backBuffer);
				ga_gameMap->RightWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->RightWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->LeftWallNoDoor->Draw(backBuffer);
				ga_gameMap->LeftWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->LeftWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
			}
			else if (type == twoDoorsTopRightWalls){
				ga_gameMap->BottomWallDoor->Draw(backBuffer);
				ga_gameMap->BottomWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->BottomWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->TopWallNoDoor->Draw(backBuffer);
				ga_gameMap->TopWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->TopWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->RightWallNoDoor->Draw(backBuffer);
				ga_gameMap->RightWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->RightWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->LeftWallDoor->Draw(backBuffer);
				ga_gameMap->LeftWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->LeftWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
			}
			else if (type == twoDoorsBottomLeftWalls){
				ga_gameMap->BottomWallNoDoor->Draw(backBuffer);
				ga_gameMap->BottomWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->BottomWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->TopWallDoor->Draw(backBuffer);
				ga_gameMap->TopWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->TopWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->RightWallDoor->Draw(backBuffer);
				ga_gameMap->RightWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->RightWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->LeftWallNoDoor->Draw(backBuffer);
				ga_gameMap->LeftWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->LeftWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
			}
			else if (type == twoDoorsBottomRightWalls){
				ga_gameMap->BottomWallNoDoor->Draw(backBuffer);
				ga_gameMap->BottomWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->BottomWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->TopWallDoor->Draw(backBuffer);
				ga_gameMap->TopWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->TopWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->RightWallNoDoor->Draw(backBuffer);
				ga_gameMap->RightWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->RightWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->LeftWallDoor->Draw(backBuffer);
				ga_gameMap->LeftWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->LeftWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
			}
			else if (type == twoDoorsSplitHorizontal){
				ga_gameMap->BottomWallNoDoor->Draw(backBuffer);
				ga_gameMap->BottomWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->BottomWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->TopWallNoDoor->Draw(backBuffer);
				ga_gameMap->TopWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->TopWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->RightWallDoor->Draw(backBuffer);
				ga_gameMap->RightWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->RightWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->LeftWallDoor->Draw(backBuffer);
				ga_gameMap->LeftWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->LeftWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
			}
			else if (type == twoDoorsSplitVertical){
				ga_gameMap->BottomWallDoor->Draw(backBuffer);
				ga_gameMap->BottomWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->BottomWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->TopWallDoor->Draw(backBuffer);
				ga_gameMap->TopWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->TopWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->RightWallNoDoor->Draw(backBuffer);
				ga_gameMap->RightWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->RightWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->LeftWallNoDoor->Draw(backBuffer);
				ga_gameMap->LeftWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->LeftWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
			}
			else if (type == oneDoorAtBottom){
				ga_gameMap->BottomWallDoor->Draw(backBuffer);
				ga_gameMap->BottomWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->BottomWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->TopWallNoDoor->Draw(backBuffer);
				ga_gameMap->TopWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->TopWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->RightWallNoDoor->Draw(backBuffer);
				ga_gameMap->RightWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->RightWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->LeftWallNoDoor->Draw(backBuffer);
				ga_gameMap->LeftWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->LeftWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
			}
			else if (type == oneDoorAtTop){
				ga_gameMap->BottomWallNoDoor->Draw(backBuffer);
				ga_gameMap->BottomWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->BottomWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->TopWallDoor->Draw(backBuffer);
				ga_gameMap->TopWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->TopWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->RightWallNoDoor->Draw(backBuffer);
				ga_gameMap->RightWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->RightWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->LeftWallNoDoor->Draw(backBuffer);
				ga_gameMap->LeftWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->LeftWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
			}
			else if (type == oneDoorOnRight){
				ga_gameMap->BottomWallNoDoor->Draw(backBuffer);
				ga_gameMap->BottomWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->BottomWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->TopWallNoDoor->Draw(backBuffer);
				ga_gameMap->TopWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->TopWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->RightWallDoor->Draw(backBuffer);
				ga_gameMap->RightWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->RightWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->LeftWallNoDoor->Draw(backBuffer);
				ga_gameMap->LeftWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->LeftWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
			}
			else if (type == oneDoorOnLeft){
				ga_gameMap->BottomWallNoDoor->Draw(backBuffer);
				ga_gameMap->BottomWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->BottomWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->TopWallNoDoor->Draw(backBuffer);
				ga_gameMap->TopWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->TopWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->RightWallNoDoor->Draw(backBuffer);
				ga_gameMap->RightWallNoDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->RightWallNoDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);

				ga_gameMap->LeftWallDoor->Draw(backBuffer);
				ga_gameMap->LeftWallDoor->SetX(playerList[clientID]->getCurrentRoomX()*screenWidth);
				ga_gameMap->LeftWallDoor->SetY(playerList[clientID]->getCurrentRoomY()*screenHeight);
			}
		}

		if (ga_hud != 0)
			ga_hud->Draw(backBuffer, minutesToBoss, secondsToBoss);

	}
	

	backBuffer.Present();
}

void 
Game::Quit()
{
	m_looping = false;
}

void
Game::adjustVolume(int xValue)
{
	ga_volumeSlider->SetX(xValue - 16);
	int value = xValue - 314;
	//0 - 592
	//592 / 10 = 59.2

	
	volumeSlide = (float) ((0 + value) / 10) / 59.2;
	ga_fmodhelp->adjustVolume(volumeSlide);
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
Game::FirePlayerBullet(int dir)
{
	
	if (playerList[clientID]->pl_bulletContainer.size() < 20)
	{
	
		Sprite* bulletSprite = m_pBackBuffer->CreateSprite("assets\\hole80.png");
		Bullet* bullet;
		switch (dir)
		{
		case 1:
			bullet = new Bullet(dir);
			bullet->Initialise(bulletSprite);

			bullet->SetPositionX(playerList[clientID]->GetPositionX() + 50);
			bullet->SetPositionY(playerList[clientID]->GetPositionY() - 17);
			bullet->setCurrentRoomX(playerList[clientID]->getCurrentRoomX());
			bullet->setCurrentRoomY(playerList[clientID]->getCurrentRoomY());
			/*bullet->SetPositionX(playerList.at(0)->GetPositionX());
			bullet->SetPositionY(playerList.at(0)->GetPositionY());*/

			bullet->setClient(clientID);
			bullet->SetVerticalVelocity(-400);
			break;
		case 2:
			bullet = new Bullet(dir);
			bullet->Initialise(bulletSprite);

			bullet->SetPositionX(playerList[clientID]->GetPositionX() + 40);
			bullet->SetPositionY(playerList[clientID]->GetPositionY() + 129);
			bullet->setCurrentRoomX(playerList[clientID]->getCurrentRoomX());
			bullet->setCurrentRoomY(playerList[clientID]->getCurrentRoomY());

			bullet->setClient(clientID);
			bullet->SetVerticalVelocity(400);
			break;
		case 3:
			bullet = new Bullet(dir);
			bullet->Initialise(bulletSprite);

			bullet->SetPositionX(playerList[clientID]->GetPositionX() - 17);
			bullet->SetPositionY(playerList[clientID]->GetPositionY() + 58);

			bullet->setCurrentRoomX(playerList[clientID]->getCurrentRoomX());
			bullet->setCurrentRoomY(playerList[clientID]->getCurrentRoomY());

			bullet->setClient(clientID);
			bullet->SetHorizontalVelocity(-400);
			break;
		case 4:
			bullet = new Bullet(dir);
			bullet->Initialise(bulletSprite);


			bullet->SetPositionX(playerList[clientID]->GetPositionX() + 125);
			bullet->SetPositionY(playerList[clientID]->GetPositionY() + 58);
			bullet->setCurrentRoomX(playerList[clientID]->getCurrentRoomX());
			bullet->setCurrentRoomY(playerList[clientID]->getCurrentRoomY());

			bullet->setClient(clientID);
			bullet->SetHorizontalVelocity(400);
			break;
		}
		//playerList.at(clientID)->pl_bulletContainer.push_back(bullet);
		playerList[clientID]->pl_bulletContainer.push_back(bullet);
		if (isServer){
			for (it_sysaddr iterator = netClients.begin(); iterator != netClients.end(); iterator++){
				RakNet::BitStream bsOut;
				bsOut.Write((RakNet::MessageID)PLAYER_SHOOT);
				bsOut.Write(clientID);
				bsOut.Write(dir);
				peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, iterator->second, false);
			}
		}
		else
		{
			RakNet::BitStream bsOut;
			bsOut.Write((RakNet::MessageID)PLAYER_SHOOT);
			bsOut.Write(clientID);
			bsOut.Write(dir);
			peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, ServerName, false);
		}
	}
	ga_fmodhelp->playSoundEffect(1);
}

void 
Game::SpawnEnemy(int x, int y)
{
	
}

void
Game::enterServerName(char* cValue)
{
	if (ga_gameState == LOBBY_JOIN){
		if (serverAdd == "IP")
		{
			SDL_Color color = { 0xFF, 0x99, 0x00, 0xFF };
			serverAdd = cValue;
			serverIP = cValue;
			ga_hostText2 = m_pBackBuffer->CreateText(serverAdd, color, "assets\\dkjalebi.otf", 42);
			ga_hostText2->SetX(550);
			ga_hostText2->SetY(350);
		}
		else
		{
			SDL_Color color = { 0xFF, 0x99, 0x00, 0xFF };
			serverIP += cValue;
			serverAdd = &serverIP[0u];
			ga_hostText2 = m_pBackBuffer->CreateText(serverAdd, color, "assets\\dkjalebi.otf", 42);
			ga_hostText2->SetX(550);
			ga_hostText2->SetY(350);
		}
	}
	else if (ga_gameState == GameState::OPTIONS_NAME)
	{
		if (name == "NAME")
		{
			SDL_Color color = { 0xFF, 0x99, 0x00, 0xFF };
			name = cValue;
			clientName = cValue;
			ga_nameChange2 = m_pBackBuffer->CreateText(name, color, "assets\\dkjalebi.otf", 42);
			ga_nameChange2->SetX(550);
			ga_nameChange2->SetY(350);
		}
		else
		{
			SDL_Color color = { 0xFF, 0x99, 0x00, 0xFF };
			clientName += cValue;
			name = &clientName[0u];
			ga_nameChange2 = m_pBackBuffer->CreateText(name, color, "assets\\dkjalebi.otf", 42);
			ga_nameChange2->SetX(550);
			ga_nameChange2->SetY(350);
		}
	}
		
	
}

void
Game::deleteServerIP()
{
	SDL_Color color = { 0xFF, 0x99, 0x00, 0xFF };
	if (ga_gameState == LOBBY_JOIN){
		if (serverIP.size() == 1 || serverIP.empty())
		{
			serverIP.clear();
			serverIP = "";
			serverAdd = "IP";
			ga_hostText2 = m_pBackBuffer->CreateText(serverAdd, color, "assets\\dkjalebi.otf", 42);
			ga_hostText2->SetX(550);
			ga_hostText2->SetY(350);
		}
		else
		{
			serverIP.erase(serverIP.size() - 1, 1);
			serverAdd = &serverIP[0u];
			ga_hostText2 = m_pBackBuffer->CreateText(serverAdd, color, "assets\\dkjalebi.otf", 42);
			ga_hostText2->SetX(550);
			ga_hostText2->SetY(350);
		}
	}
	else if (ga_gameState == OPTIONS_NAME)
	{
		if (clientName.size() == 1 || clientName.empty())
		{
			clientName.clear();
			clientName = "";
			name = "NAME";
			ga_nameChange2 = m_pBackBuffer->CreateText(name, color, "assets\\dkjalebi.otf", 42);
			ga_nameChange2->SetX(550);
			ga_nameChange2->SetY(350);
		}
		else
		{
			clientName.erase(clientName.size() - 1, 1);
			name = &clientName[0u];
			ga_nameChange2 = m_pBackBuffer->CreateText(name, color, "assets\\dkjalebi.otf", 42);
			ga_nameChange2->SetX(550);
			ga_nameChange2->SetY(350);
		}
	}
	

}


void
Game::initiateServer()
{
	//Sprite* pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\playership.png");


	//Player* player = new Player();
	//player->Initialise(pPlayerSprite);
	//player->SetPositionX(screenWidth / 2);
	//player->SetPositionY(screenHeight / 2);


	RakNet::SocketDescriptor sd(SERVER_PORT, 0);
	peer->SetMaximumIncomingConnections(MAX_CONNS);
	peer->Startup(MAX_CONNS, &sd, 1);
	isServer = true;
	//serverInitiated = true;
	printf("Server is ready to receive connections.\n");
	//name = "Server";
	serverAdd = (char*) peer->GetLocalIP(0);
	//playerList[0] = player;
	clientNames[0] = name;

	SDL_Color color = { 0xFF, 0x99, 0x00, 0xFF };
	Sprite* pText = m_pBackBuffer->CreateText(name, color, "assets\\dkjalebi.otf", 42);
	pText->SetX(140);
	pText->SetY(10 * clientID + 160);

	ga_lobbyHost->SetX(screenWidth / 2 - 300);
	ga_lobbyHost->SetY(screenHeight / 2 - 200);

	ga_hostText1 = m_pBackBuffer->CreateText("Your ip is: ", color, "assets\\dkjalebi.otf", 42);
	ga_hostText1->SetX(550);
	ga_hostText1->SetY(580);

	ga_hostText2 = m_pBackBuffer->CreateText(serverAdd, color, "assets\\dkjalebi.otf", 42);
	ga_hostText2->SetX(550);
	ga_hostText2->SetY(630);

	playerL2TextList[0] = pText;
	//ga_gameState = LOBBY;

	std::thread nt(NetworkThread);

	nt.detach();
}

void
Game::disconnectClient()
{
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)PLAYER_DISCONNECT);
	bsOut.Write(clientID);
	peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, ServerName, false);


	
	

}

void
Game::initiateClient()
{
	if (!isServer){
		


		RakNet::SocketDescriptor sd;
		peer->Startup(1, &RakNet::SocketDescriptor(), 1);
		isServer = false;
		printf("Client is connecting to %s:%d\n", SERVER_ADDR, SERVER_PORT);
		peer->Connect(serverAdd, SERVER_PORT, 0, 0);
		ga_gameState = LOBBY;
		std::thread nt(NetworkThread);

		nt.detach();
	}
}

void
Game::startGame()
{
	if (isServer)
	{
		ga_gameState = RUNNING;
		ga_fmodhelp->playBackgroundMusic(2);

		srand(time(0));


		Game& game = Game::GetGame();
		//game.MoveSpaceShipRight(y);
		BackBuffer* backBuffer = game.CallBackBuffer();
		AnimatedSprite* pPlayerSprite = backBuffer->CreateAnimatedSprite("assets\\playerIdle.png");
		//Sprite* pPlSprite = backBuffer->CreateAnimatedSprite("assets\\playership.png");

		Player* player = new Player();
		player->Initialise(pPlayerSprite);
		player->SetPositionX(screenWidth / 2);
		player->SetPositionY(screenHeight / 2);

		playerList[0] = player;
		clientID = 0;

		for (it_sysaddr iterator = netClients.begin(); iterator != netClients.end(); iterator++)
		{
			int roomX = (rand()) % 10;
			float roomY = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 400.0);
			float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 400.0);
			float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 400.0);
			AnimatedSprite* pPlayerSprite = backBuffer->CreateAnimatedSprite("assets\\playerIdle.png");
			Player* pl = new Player();
			pl->Initialise(pPlayerSprite);
			pl->SetPositionX(x);
			pl->SetPositionY(y);
			playerList[iterator->first] = pl;
			RakNet::BitStream IDreturn;
			IDreturn.Write((RakNet::MessageID)CLIENT_ID);
			IDreturn.Write(iterator->first);
			peer->Send(&IDreturn, HIGH_PRIORITY, RELIABLE_ORDERED, 0, iterator->second, false);

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
		for (it_sysaddr iterator = netClients.begin(); iterator != netClients.end(); iterator++)
		{
			peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, iterator->second, false);
		}
		hudCreated = true;
		playerCreated = true;

		serverInitiated = true;
	}
}

/////// Liam
void
NetworkThread()
{

	Game& game = Game::GetGame();
	//game.MoveSpaceShipRight(y);
	BackBuffer* backBuffer = game.CallBackBuffer();


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
				{
					printf("A remote system has disconnected.\n");

					int id;
					for (it_sysaddr iterator = netClients.begin(); iterator != netClients.end(); iterator++)
					{
						if (packet->systemAddress == iterator->second)
						{
							id = iterator->first;
						}
					}

					netClients.erase(id);
					clientNames.erase(id);
					playerList.erase(id);

					for (it_players iterator = playerList.begin(); iterator != playerList.end(); iterator++)
					{
						if (iterator->first > id){
							clientNames[iterator->first - 1] = clientNames.at(iterator->first);
							netClients[iterator->first - 1] = netClients.at(iterator->first);
							playerList[iterator->first - 1] = iterator->second;

						}
					}

					netClients.erase(playerList.size() + 1);
					clientNames.erase(playerList.size() + 1);
					playerList.erase(playerList.size() + 1);




					RakNet::BitStream bsOut;
					bsOut.Write((RakNet::MessageID)PLAYER_DISCONNECT);
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
				case ID_CONNECTION_LOST:
				{
					printf("A remote system lost the connection.\n");
					int id;
					for (it_sysaddr iterator = netClients.begin(); iterator != netClients.end(); iterator++)
					{
						if (packet->systemAddress == iterator->second)
						{
							id = iterator->first;
						}
					}

					netClients.erase(id);
					clientNames.erase(id);
					playerList.erase(id);

					for (it_players iterator = playerList.begin(); iterator != playerList.end(); iterator++)
					{
						if (iterator->first > id){
							clientNames[iterator->first - 1] = clientNames.at(iterator->first);
							netClients[iterator->first - 1] = netClients.at(iterator->first);
							playerList[iterator->first - 1] = iterator->second;

						}
					}

					netClients.erase(playerList.size() + 1);
					clientNames.erase(playerList.size() + 1);
					playerList.erase(playerList.size() + 1);




					RakNet::BitStream bsOut;
					bsOut.Write((RakNet::MessageID)PLAYER_DISCONNECT);
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
				case NEW_PLAYER:
				{

					float x, y;
					RakNet::BitStream bsIn(packet->data, packet->length, false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(x);
					bsIn.Read(y);



					AnimatedSprite* pPlayerSprite = backBuffer->CreateAnimatedSprite("assets\\playerIdle.png");
					Player* pl = new Player();
					pl->Initialise(pPlayerSprite);
					pl->SetPositionX(x);
					pl->SetPositionY(y);

					int i = playerList.size();
					playerList[i] = pl;
					clientNames[i] = name;




					RakNet::BitStream IDreturn;
					IDreturn.Write((RakNet::MessageID)CLIENT_ID);
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
					{

						playerList.at(i)->SetHorizontalVelocity(speed);
					}
					//	e->SetHorizontalVelocity(speed);
					else if (dirCheck == 1)
					{

						playerList.at(i)->SetVerticalVelocity(speed);
					}

				}
					break;
				case NET_UPDATE:
				{

				}
				case PLAYER_DISCONNECT:
				{
					int id;
					RakNet::BitStream bsIn(packet->data, packet->length, false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(id);
					netClients.erase(id);
					playerList.erase(id);

					for (it_players iterator = playerList.begin(); iterator != playerList.end(); iterator++)
					{
						if (iterator->first > id){
							netClients[iterator->first - 1] = netClients.at(iterator->first);
							playerList[iterator->first - 1] = iterator->second;
						}
					}

					netClients.erase(playerList.size() + 1);
					playerList.erase(playerList.size() + 1);



					RakNet::BitStream bsOut;
					bsOut.Write((RakNet::MessageID)PLAYER_DISCONNECT);
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

					RakNet::BitStream bsReturn;
					bsReturn.Write((RakNet::MessageID)CLIENT_END);
					bool endVal = true;
					bsReturn.Write(endVal);
					peer->Send(&bsReturn, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);




				}
					break;
				case LOBBY_NEW_PLAYER:
				{
					char client[] = "";
					RakNet::BitStream bsIn(packet->data, packet->length, false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(client);
					name = client;
					int i = clientNames.size();
					clientNames[i] = name;

					SDL_Color color = { 0xFF, 0x99, 0x00, 0xFF };
					Sprite* pText = backBuffer->CreateText(name, color, "assets\\dkjalebi.otf", 42);

					pText->SetX(140);
					pText->SetY(40 * (i)+160);

					playerL2TextList[i] = pText;

					RakNet::BitStream bsOut;
					bsOut.Write((RakNet::MessageID)LOBBY_NEW_PLAYER);

					int plSize = clientNames.size();
					bsOut.Write(plSize);

					for (it_L2Text iterator = playerL2TextList.begin(); iterator != playerL2TextList.end(); iterator++)
					{
						Sprite* e = iterator->second;
						int j = iterator->first;
						bsOut.Write(clientNames.at(iterator->first));
						bsOut.Write(e->GetX());
						bsOut.Write(e->GetY());
					}
					for (it_sysaddr iterator = netClients.begin(); iterator != netClients.end(); iterator++)
					{
						peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, iterator->second, false);
					}

				}
					break;
				case PLAYER_SHOOT:
				{
					int i;
					int dirCheck;
					RakNet::BitStream bsIn(packet->data, packet->length, false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(i);
					bsIn.Read(dirCheck);
					//int i;

					//for (it_sysaddr iterator = netClients.begin(); iterator != netClients.end(); iterator++){
					//if (packet->systemAddress == iterator->second)
					//{
					//	i = iterator->first;
					//}
					//}

					for (it_sysaddr iterator = netClients.begin(); iterator != netClients.end(); iterator++){
						if (iterator->first != i){
							RakNet::BitStream bsOut;
							bsOut.Write((RakNet::MessageID)PLAYER_SHOOT);
							bsOut.Write(i);
							bsOut.Write(dirCheck);
							peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, iterator->second, false);
						}
					}


					Sprite* bulletSprite = backBuffer->CreateSprite("assets\\hole80.png");
					Bullet* bullet = new Bullet(dirCheck);
					bullet->Initialise(bulletSprite);
					bullet->SetPositionX(playerList[i]->GetPositionX() + 40);
					bullet->SetPositionY(playerList[i]->GetPositionY() + 40);
					bullet->setClient(i);
					switch (dirCheck)
					{
					case 1:
					{
							bullet->SetVerticalVelocity(-400);
							//bullet->setCurrentRoomX(playerList[clientID]->getCurrentRoomX());
							//bullet->setCurrentRoomY(playerList[clientID]->getCurrentRoomY());
					}
						break;
					case 2:
					{
							bullet->SetVerticalVelocity(400);
					}
						break;
					case 3:
					{
							bullet->SetHorizontalVelocity(-400);
					}
						break;
					case 4:
					{
							bullet->SetHorizontalVelocity(400);
					}
						break;
					}

					//playerList.at(i)->pl_bulletContainer.push_back(bullet);
					playerList[i]->pl_bulletContainer.push_back(bullet);

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
					//char name[] = "John";
					//float x, y;
					//x = 300.0;
					// y = 200.0;


					bsOut.Write((RakNet::MessageID)LOBBY_NEW_PLAYER);
					bsOut.Write(name);
					//bsOut.Write(x);
					//bsOut.Write(y);
					peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, ServerName, false);
					break;
				}
				case PLAYER_LIST:
				{

					Game& game = Game::GetGame();
					game.ga_gameState = RUNNING;


					//playerList.clear();
					int plSize;
					RakNet::BitStream bsIn(packet->data, packet->length, false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(plSize);
					for (int i = 0; i < plSize; i++)
					{

						//game.MoveSpaceShipRight(y);
						BackBuffer* backBuffer = game.CallBackBuffer();
						AnimatedSprite* pPlayerSprite = backBuffer->CreateAnimatedSprite("assets\\playerIdle.png");
						Player* pl = new Player();
						pl->Initialise(pPlayerSprite);
						float x, y;
						bsIn.Read(x);
						bsIn.Read(y);

						pl->SetPositionX(x);
						pl->SetPositionY(y);
						playerList[i] = pl;
					}

					hudCreated = true;
					playerCreated = true;
					serverInitiated = true;

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

					if (dirCheck == 0)
					{
						playerList.at(i)->SetHorizontalVelocity(speed);
					}
					//	e->SetHorizontalVelocity(speed);
					else if (dirCheck == 1)
					{

						playerList.at(i)->SetVerticalVelocity(speed);
					}



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
				case PLAYER_DISCONNECT:
				{
					playerList.clear();
					//playerList.clear();
					int plSize;
					RakNet::BitStream bsIn(packet->data, packet->length, false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(plSize);
					for (int i = 0; i < plSize; i++)
					{
						Game& game = Game::GetGame();
						//game.MoveSpaceShipRight(y);
						BackBuffer* backBuffer = game.CallBackBuffer();
						AnimatedSprite* pPlayerSprite = backBuffer->CreateAnimatedSprite("assets\\playerIdle.png");
						Player* pl = new Player();
						pl->Initialise(pPlayerSprite);
						float x, y;
						bsIn.Read(x);
						bsIn.Read(y);

						pl->SetPositionX(x);
						pl->SetPositionY(y);

						playerList[i] = pl;
					}

					serverInitiated = true;
				}
					break;
				case CLIENT_END:
				{

					serverInitiated = false;
					isRunning = false;


				}
					break;
				case LOBBY_NEW_PLAYER:
				{

					SDL_Color color = { 0xFF, 0x99, 0x00, 0xFF };
					//playerList.clear();
					int plSize;
					RakNet::BitStream bsIn(packet->data, packet->length, false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(plSize);
					for (int i = 0; i < plSize; i++)
					{
						int x, y;

						char client[] = "";

						bsIn.Read(client);
						bsIn.Read(x);
						bsIn.Read(y);
						char* name = client;

						clientNames[i] = name;

						Sprite* pText = backBuffer->CreateText(name, color, "assets\\dkjalebi.otf", 42);
						pText->SetX(x);
						pText->SetY(y);

						playerL2TextList[i] = pText;
					}
				}
					break;
				case PLAYER_SHOOT:
				{
					int dirCheck;
					int id;
					RakNet::BitStream bsIn(packet->data, packet->length, false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(id);
					bsIn.Read(dirCheck);



					Sprite* bulletSprite = backBuffer->CreateSprite("assets\\hole80.png");
					Bullet* bullet = new Bullet(dirCheck);
					bullet->Initialise(bulletSprite);
					bullet->SetPositionX(playerList[id]->GetPositionX() + 40);
					bullet->SetPositionY(playerList[id]->GetPositionY() + 40);
					switch (dirCheck)
					{
					case 1:
					{
							bullet->SetVerticalVelocity(-400);
							bullet->setClient(id);
					}
						break;
					case 2:
					{
							bullet->SetVerticalVelocity(400);
							bullet->setClient(id);
					}
						break;
					case 3:
					{
							bullet->SetHorizontalVelocity(-400);
							bullet->setClient(id);
					}
						break;
					case 4:
					{
							bullet->SetHorizontalVelocity(400);
							bullet->setClient(id);
					}
						break;
					}

					//playerList.at(id)->pl_bulletContainer.push_back(bullet);
					playerList[id]->pl_bulletContainer.push_back(bullet);
					
					
				}
					break;
				}

				}


			}
			Sleep(10);

		}
		netClients.clear();
		playerList.clear();

		//peer->CloseConnection(ServerName, 0);

		RakNet::RakPeerInterface::DestroyInstance(peer);

		peer = RakNet::RakPeerInterface::GetInstance();
}

BackBuffer*
Game::CallBackBuffer()
{
	return m_pBackBuffer;
}


void
Game::updateCamera(){
	if (ga_gameState == RUNNING && serverInitiated){
		float charPosX = playerList[clientID]->GetPositionX();
		float charPosY = playerList[clientID]->GetPositionY();

		int roomX = playerList[clientID]->getCurrentRoomX();
		int roomY = playerList[clientID]->getCurrentRoomY();

		m_pBackBuffer->SetCameraX(roomX*screenWidth);
		m_pBackBuffer->SetCameraY(roomY*screenHeight);
	}

}

void
	Game::addHealth(){
	playerList.at(clientID)->setHealth(playerList.at(clientID)->getHealth() + 10);
}

void
	Game::minusHealth(){
	playerList.at(clientID)->setHealth(playerList.at(clientID)->getHealth() - 10);
}