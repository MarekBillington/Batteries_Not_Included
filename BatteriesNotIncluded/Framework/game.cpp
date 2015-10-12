// 717310 C++ SDL Framework

// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"

// Library includes:
#include <cassert>
#include <SDL.h>

// Static Members:
Game* Game::sm_pInstance = 0;

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
	const int width = 800;
	const int height = 600;

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

	// Ex006.2: Load the player ship sprite.
	// For example: Sprite* pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\playership.png");

	// Ex006.2: Create the player ship instance.

	// Ex006.3: Spawn four rows of 14 alien enemies.

	// Ex006.3: Fill the container with these new enemies.

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

	// Ex006.2: Draw the player ship...

	backBuffer.Present();
}

void 
Game::Quit()
{
	m_looping = false;
}

void 
Game::MoveSpaceShipLeft()
{
	// Ex006.2: Tell the player ship to move left.
	//m_playerShip->setHorizontalVelocity(-100);        
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
