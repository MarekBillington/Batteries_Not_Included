// 717310 C++ SDL Framework

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"

// Library includes:
#include <cassert>

InputHandler::InputHandler()
: m_pGameController(0)
{

}

InputHandler::~InputHandler()
{
	if (m_pGameController)
	{
		SDL_JoystickClose(m_pGameController);
		m_pGameController = 0;
	}
}

bool 
InputHandler::Initialise()
{
	int numControllesr = SDL_NumJoysticks();

	m_pGameController = SDL_JoystickOpen(0);
	//assert(m_pGameController);

	return (true);
}

void 
InputHandler::ProcessInput(Game& game)
{
	// Ex006.2: Receive Input Events below...
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (e.type == SDL_JOYBUTTONDOWN)
		{
			// Ex006.4: Tell the game to fire a player bullet...
			if (e.jbutton.button == 10)
			{
				//game.FireSpaceShipBullet();
			}

			// Ex006.2: Tell the game to move the space ship left...

			// Ex006.2: Tell the game to move the space ship right...
		}
	}
}
