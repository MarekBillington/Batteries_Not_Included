// 717310 C++ SDL Framework

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"
#include "fmodhelper.h"
// Library includes:
#include <cassert>
#include <string>

char* text;

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
	if (game.ga_gameState == LOBBY_JOIN)
	{
		SDL_StartTextInput();
	}
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
					game.ga_gameState = GameState::OPTIONS;
				}
				if (460 < x && x < 820 && 336 < y && y < 407){
					//go to multiplayer lobby
					game.ga_gameState = GameState::LOBBY_CHOOSE;
					//game.ga_fmodhelp->playBackgroundMusic(2);
				}
				if (460 < x && x < 820 && 216 < y && y < 286){
					//go to training map
					game.ga_gameState = GameState::RUNNING;
					game.ga_fmodhelp->playBackgroundMusic(2);
				}
			}	//main menu bracket

		}
		if (game.ga_gameState == OPTIONS)
		{
			if (e.type == SDL_MOUSEBUTTONDOWN){
				int x;
				int y;
				SDL_GetMouseState(&x, &y);
				if (416 < x && x < 826 && 208 < y && y < 338){
					//go to training map
					game.ga_gameState = GameState::OPTIONS_NAME;
				}
				if (324 < x && x < 916 && 524 < y && y < 542)
				{
					game.adjustVolume(x);
				}
			}
			if (e.type == SDL_KEYDOWN){

				
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					game.ga_gameState = GameState::MAINMENU;
					//game.initiateServer();
					//game.ga_gameState = LOBBY;
				}
			}
		} 
		if (game.ga_gameState == OPTIONS_NAME)
		{
			if (e.type == SDL_TEXTINPUT)
			{
				if (text == NULL)
				{
					text = e.text.text;
				}
				game.enterServerName(text);
				text = NULL;
				//	printf("ok");
			}
			if (e.type == SDL_KEYDOWN){

				if (e.key.keysym.sym == SDLK_RETURN)
				{
					SDL_StopTextInput();
					game.ga_gameState = GameState::OPTIONS;
					//game.initiateClient();
					//game.initiateServer();
					//game.ga_gameState = LOBBY;
				}
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					SDL_StopTextInput();
					game.ga_gameState = GameState::OPTIONS;
					//game.initiateServer();
					//game.ga_gameState = LOBBY;
				}
				if (e.key.keysym.sym == SDLK_BACKSPACE)
				{
					game.deleteServerIP();
				}
			}
		}
		if (game.ga_gameState == LOBBY_CHOOSE)
		{
			if (e.type == SDL_MOUSEBUTTONDOWN){
				//remember to uncomment the related brackeT
				int x;
				int y;
				SDL_GetMouseState(&x, &y);
				if (494 < x && x < 784 && 234 < y && y < 338){
					//Host lobby
					game.ga_gameState = LOBBY;
					game.initiateServer();
				}

				if (494 < x && x < 784 && 424 < y && y < 534){
					//Join lobby
					game.ga_gameState = LOBBY_JOIN;
					//game.initiateClient();
				}
			}

			if (e.type == SDL_KEYDOWN){
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					//Quit choosing screen
					game.ga_gameState = GameState::MAINMENU;
				}
			}
		}
	
		if (game.ga_gameState == LOBBY_JOIN)
		{
			
			if (e.type == SDL_TEXTINPUT)
			{
				if (text == NULL)
				{
					text = e.text.text;
				}
				game.enterServerName(text);
				text = NULL;
			//	printf("ok");
			}
			if (e.type == SDL_KEYDOWN){
				
				if (e.key.keysym.sym == SDLK_RETURN)
				{
					SDL_StopTextInput();
					game.initiateClient();
					//game.initiateServer();
					//game.ga_gameState = LOBBY;
				}
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					SDL_StopTextInput();
					game.ga_gameState = GameState::LOBBY_CHOOSE;
					//game.initiateServer();
					//game.ga_gameState = LOBBY;
				}
				if (e.key.keysym.sym == SDLK_BACKSPACE)
				{
					game.deleteServerIP();
					//game.initiateServer();
					//game.ga_gameState = LOBBY;
				}
			}
		}
		if (game.ga_gameState == LOBBY)
		{
			if (e.type == SDL_MOUSEBUTTONDOWN){
				//remember to uncomment the related bracket

				int x;
				int y;
				SDL_GetMouseState(&x, &y);
				if (134 < x && x < 441 && 578 < y && y < 674){
					//Start Lobby Game
					
					game.ga_fmodhelp->playBackgroundMusic(2);
					game.startGame();
				}
				else if (915 < x && x < 1164 && 578 < y && y < 674)
				{
					game.Reset();
				}
				
			}	//lobby bracket

			if (e.type == SDL_KEYDOWN){
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					SDL_StopTextInput();
					game.ga_gameState = GameState::MAINMENU;
					//game.initiateServer();
					//game.ga_gameState = LOBBY;
				}
			}
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
				else if (e.key.keysym.sym == SDLK_t)
				{
					game.addHealth();
				}
				else if (e.key.keysym.sym == SDLK_y)
				{
					game.minusHealth();
				}
				else if (e.key.keysym.sym == SDLK_m)
				{
					game.minutesToBoss = 0;
					game.secondsToBoss = 0;
				}
				else if (e.key.keysym.sym == SDLK_3)
				{
					game.ga_hud->mapType = !game.ga_hud->mapType;
				}
				else if (e.key.keysym.sym == SDLK_o)
				{
					game.disconnectClient();
				}
				else if (e.key.keysym.sym == SDLK_d)
				{
					game.MoveSpaceShipHor(300);
				}
				else if (e.key.keysym.sym == SDLK_a)
				{
					game.MoveSpaceShipHor(-300);
				}
				else if (e.key.keysym.sym == SDLK_w)
				{
					game.MoveSpaceShipVert(-300);
				}
				else if (e.key.keysym.sym == SDLK_s)
				{
					game.MoveSpaceShipVert(300);
				}
				else if (e.key.keysym.sym == SDLK_UP)
				{
					game.FirePlayerBullet(1);
				}
				else if (e.key.keysym.sym == SDLK_DOWN)
				{
					game.FirePlayerBullet(2);
				}
				else if (e.key.keysym.sym == SDLK_LEFT)
				{
					game.FirePlayerBullet(3);
				}
				else if (e.key.keysym.sym == SDLK_RIGHT)
				{
					game.FirePlayerBullet(4);
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

