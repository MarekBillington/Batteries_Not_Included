// 717310 C++ SDL Framework
#ifndef __GAME_H__
#define __GAME_H__

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;

class Entity;
class Player;
class GameMap;
class FMODHelper;

#include "hud.h"

enum GameState
{
	MAINMENU,
	LOBBY_CHOOSE,
	LOBBY_HOST,
	LOBBY_JOIN,
	RUNNING,
	LOBBY,
	OPTIONS,
	OPTIONS_NAME,
	OPTIONS_VOLUME
};

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();

	static Game& GetGame();

	bool Initialise();
	bool DoGameLoop();
	void Quit();
	void Reset();

	void adjustVolume(int xValue);

	void MoveSpaceShipHor(float speed);
	void MoveSpaceShipVert(float speed);
	BackBuffer* CallBackBuffer();
	void ServerMoveShip();
	
	void FirePlayerBullet(int dir);

	void MoveSpaceShipLeft();

	void SpawnEnemy(int x, int y);
	void SpawnExplosion(int x, int y);

	void initiateServer();
	void initiateClient();
	void startGame();

	void enterServerName(char* cValue);
	void deleteServerIP();

	void disconnectClient();

	//ryan
	GameState ga_gameState;

	//tom
	void updateCamera();
	FMODHelper* ga_fmodhelp;
	
	//james
	void addHealth();
	void minusHealth();
	Hud* ga_hud;

protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	//Member Data:
public:
	int secondsToBoss;
	int minutesToBoss;
	bool bossTime = false;
protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	bool m_looping;

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	int m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;

	// Game Entities:
	// Ex006.2: Add a PlayerShip field.    
	// Ex006.3: Add an alien enemy container field.
	// Ex006.4: Add a bullet container field.


	//marek
	//liam
	//ryan
	Sprite* ga_mainMenu;
	Sprite* ga_lobbyChoose;
	Sprite* ga_lobbyWait;
	Sprite* ga_lobbyHost;
	Sprite* ga_hostText1;
	Sprite* ga_hostText2;
	Sprite* ga_options;
	Sprite* ga_nameBox;
	Sprite* ga_nameChange1;
	Sprite* ga_nameChange2;
	Sprite* ga_volumeSlider;

	Sprite* currentIP;
	//Player* player;


	//james
	//tom
	GameMap* ga_gameMap;
	int screenWidth;
	int screenHeight;
	
	// stuff
private:

};

#endif // __GAME_H__
