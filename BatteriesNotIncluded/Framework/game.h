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

enum GameState
{
	MAINMENU,
	RUNNING
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

	void MoveSpaceShipHor(float speed);
	void MoveSpaceShipVert(float speed);
	BackBuffer* CallBackBuffer();
	void ServerMoveShip();
	void FireSpaceShipBullet();

	void MoveSpaceShipLeft();

	void SpawnEnemy(int x, int y);
	void SpawnExplosion(int x, int y);

	void initiateServer();
	void initiateClient();

	void disconnectClient();

	//ryan
	GameState ga_gameState;

	//tom
	void updateCamera();
	FMODHelper* ga_fmodhelp;
	
protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	//Member Data:
public:

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
	Player* player;


	//james
	//tom
	GameMap* ga_gameMap;
	int screenWidth;
	int screenHeight;
	
	
private:

};

#endif // __GAME_H__
