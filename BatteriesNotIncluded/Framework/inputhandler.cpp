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

		if (game.ga_gameState == GameState::MAINMENU){
			if (e.type == SDL_MOUSEBUTTONDOWN){
				//remember to uncomment the related bracket

				int x;
				int y;
				SDL_GetMouseState(&x, &y);
				if (460 < x && x < 820 && 578 < y && y < 648){
					//quit game via menu
					game.Quit();
				}
				if (460 < x && x < 820 && 457 < y && y < 528){
					//go options menu
				}
				if (460 < x && x < 820 && 336 < y && y < 407){
					//go to multiplayer lobby
					game.ga_gameState = GameState::RUNNING;
				}
				if (460 < x && x < 820 && 216 < y && y < 286){
					//go to training map
					game.ga_gameState = GameState::RUNNING;
				}
			}	//main menu bracket

		}
		if (game.ga_gameState == GameState::RUNNING){
			if (e.type == SDL_KEYDOWN){
				if (e.key.keysym.sym == SDLK_u)
				{
					game.initiateServer();
				}
				else if (e.key.keysym.sym == SDLK_i)
				{
					game.initiateClient();
				}
				else if (e.key.keysym.sym == SDLK_d)
				{
					game.MoveSpaceShipHor(100);
				}
				else if (e.key.keysym.sym == SDLK_a)
				{
					game.MoveSpaceShipHor(-100);
				}
				else if (e.key.keysym.sym == SDLK_w)
				{
					game.MoveSpaceShipVert(-100);
				}
				else if (e.key.keysym.sym == SDLK_s)
				{
					game.MoveSpaceShipVert(100);
				}
			}
			else if (e.type == SDL_KEYUP){

				if (e.key.keysym.sym == SDLK_d)
				{
					game.MoveSpaceShipHor(0);
				}
				else if (e.key.keysym.sym == SDLK_a)
				{
					game.MoveSpaceShipHor(0);
				}
				else if (e.key.keysym.sym == SDLK_w)
				{
					game.MoveSpaceShipVert(0);
				}
				else if (e.key.keysym.sym == SDLK_s)
				{
					game.MoveSpaceShipVert(0);
				}
			}
		}	
	}
}

