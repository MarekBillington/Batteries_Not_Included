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

		if (/*game state == main menu*/ false){
			if (e.type == SDL_MOUSEBUTTONDOWN){
				//remember to uncomment the related bracket

				int x;
				int y;
				SDL_GetMouseState(&x, &y);
				if (460 < x && x < 820 && 578 < y && y < 648){
					//quit game via menu
				}
				if (460 < x && x < 820 && 457 < y && y < 528){
					//go options menu
				}
				if (460 < x && x < 820 && 336 < y && y < 407){
					//go to multiplayer lobby
				}
				if (460 < x && x < 820 && 216 < y && y < 286){
					//go to training map
				}
			}	//main menu bracket

		}
		if (/*&& game state is == ingame*/ true){
			if (e.type == SDLK_w){
				//insert method to move player up
			}
			if (e.type == SDLK_s){
				//insert method to move player down
			}
			if (e.type == SDLK_d){
				//insert method to move player right
			}
			if (e.type == SDLK_a){
				//insert method to move player left
			}
			if (e.type == SDLK_UP){
				//insert method to move attack upwards
			}
			if (e.type == SDLK_RIGHT){
				//insert method to attack rightwards
			}
			if (e.type == SDLK_LEFT){
				//insert method to attack leftwards
			}
			if (e.type == SDLK_DOWN){
				//insert method to attack downwards
			}
			if (e.type == SDLK_q){
				//insert method to cycle passives left
			}
			if (e.type == SDLK_e){
				//insert method to cycle passives right
			}
			if (e.type == SDLK_SPACE){
				//method to use active class ability
			}
			if (e.type == SDLK_f){
				//method to drop passive
			}

		}	
	}
}

