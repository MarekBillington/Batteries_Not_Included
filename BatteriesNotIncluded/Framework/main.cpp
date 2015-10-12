// 717310 C++ SDL Framework

// Library includes:
#include <SDL.h>

// Local includes:
#include "game.h"
#include "logmanager.h"

int main(int argc, char* argv[])
{
	Game& gameInstance = Game::GetInstance();
	if (!gameInstance.Initialise())
	{
		LogManager::GetInstance().Log("Game Init Failed!");

		return (1);
	}
	
	while (gameInstance.DoGameLoop())
	{
		// No body.
	}

	Game::DestroyInstance();

	return (0);
}
