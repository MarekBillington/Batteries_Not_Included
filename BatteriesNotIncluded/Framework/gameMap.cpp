#include "gameMap.h"
#include "room.h"
#include <fstream>
#include "game.h"
#include "backbuffer.h"

GameMap::GameMap()
{
}

GameMap::~GameMap()
{
}


void
GameMap::parseFile()
{
	
	gm_layout[9][9];
	std::ifstream mapfile;
	mapfile.open("assets\\map_2.txt");

	Game& game = Game::GetGame();
	BackBuffer* backBuffer = game.CallBackBuffer();

	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			
			Sprite* roomSprite;
			
			char c;
			mapfile >> c;
			if ((int)c == 48)
			{
				gm_room = fourDoors;
				roomSprite = backBuffer->CreateSprite("assets\\AllDoorsOpenRoom1280.png");
			}
			else if ((int)c == 49)
			{
				gm_room = threeDoorsTopWall;
				roomSprite = backBuffer->CreateSprite("assets\\AllDoorsOpenRoom1280-2.png");
			}
			else if ((int)c == 50)
			{
				gm_room = threeDoorsBottomWall;
				roomSprite = backBuffer->CreateSprite("assets\\AllDoorsOpenRoom1280-3.png");
			}
			else if ((int)c == 51)
			{
				gm_room = threeDoorsLeftWall;
				roomSprite = backBuffer->CreateSprite("assets\\AllDoorsOpenRoom1280-4.png");
			}
			else if ((int)c == 52)
			{
				gm_room = threeDoorsRightWall;
			}
			else if ((int)c == 53)
			{
				gm_room = twoDoorsTopLeftWalls;
			}
			else if ((int)c == 54)
			{
				gm_room = twoDoorsTopRightWalls;
			}
			else if ((int)c == 55)
			{
				gm_room = twoDoorsBottomLeftWalls;
			}
			else if ((int)c == 56)
			{
				gm_room = twoDoorsBottomRightWalls;
			}
			else if ((int)c == 57)
			{
				gm_room = twoDoorsSplitHorizontal;
			}
			else if ((int)c == 97)
			{
				gm_room = twoDoorsSplitVertical;
			}
			else if ((int)c == 98)
			{
				gm_room = oneDoorAtBottom;
			}
			else if ((int)c == 99)
			{
				gm_room = oneDoorAtTop;
			}
			else if ((int)c == 100)
			{
				gm_room = oneDoorOnRight;
			}
			else if ((int)c == 101)
			{
				gm_room = oneDoorOnLeft;
			}
			else 
			{
				gm_room = blank;
				roomSprite = backBuffer->CreateSprite("assets\\AllDoorsClosedRoom1280.png");
			}

			Room* room = new Room(i,j);
			room->Initialise(roomSprite);
			room->setRoomNumber(gm_room);
			gm_layout[i][j] = room;
		}
	}
}


void
GameMap::draw(BackBuffer& backbuffer){
	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			gm_layout[i][j]->Draw(backbuffer);
		}
	}
}





Room*
GameMap::getRoomAt(int i, int j){
	return gm_layout[i][j];
}

void
GameMap::setRoomAt(int i, int j, Room* value){
	gm_layout[i][j] = value;
}