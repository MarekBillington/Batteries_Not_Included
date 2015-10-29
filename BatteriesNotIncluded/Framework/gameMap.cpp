#include "gameMap.h"
//#include "room.h"
#include <fstream>
#include "game.h"
#include "backbuffer.h"

GameMap::GameMap(BackBuffer* backbuffer)
{
	BottomWallDoor = backbuffer->CreateSprite("assets\\Bottom_Wall_Door.png");
	TopWallDoor = backbuffer->CreateSprite("assets\\Top_Wall_Door.png");
	RightWallDoor = backbuffer->CreateSprite("assets\\Right_Wall_Door.png");
	LeftWallDoor = backbuffer->CreateSprite("assets\\Left_Wall_Door.png");

	BottomWallNoDoor = backbuffer->CreateSprite("assets\\Bottom_Wall_No_Door.png");
	TopWallNoDoor = backbuffer->CreateSprite("assets\\Top_Wall_No_Door.png");
	RightWallNoDoor = backbuffer->CreateSprite("assets\\Right_Wall_No_Door.png");
	LeftWallNoDoor = backbuffer->CreateSprite("assets\\Left_Wall_No_Door.png");
}

GameMap::~GameMap()
{
}

void
GameMap::parseFile()
{
	
	gm_layout[9][9];
	std::ifstream mapfile;
	mapfile.open("assets\\map_3.txt");

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
			{//0
				gm_room = fourDoors;
				roomSprite = backBuffer->CreateSprite("assets\\AllDoorsOpenRoom.png");
			}
			else if ((int)c == 49)
			{//1
				gm_room = threeDoorsTopWall;
				roomSprite = backBuffer->CreateSprite("assets\\threeDoorsTopWallOpen.png");
			}
			else if ((int)c == 50)
			{//2
				gm_room = threeDoorsBottomWall;
				roomSprite = backBuffer->CreateSprite("assets\\threeDoorsBottomWallOpen.png");
			}
			else if ((int)c == 51)
			{//3
				gm_room = threeDoorsLeftWall;
				roomSprite = backBuffer->CreateSprite("assets\\threeDoorsLeftWallOpen.png");
			}
			else if ((int)c == 52)
			{//4
				gm_room = threeDoorsRightWall;
				roomSprite = backBuffer->CreateSprite("assets\\threeDoorsRightWallOpen.png");
			}
			else if ((int)c == 53)
			{//5
				gm_room = twoDoorsTopLeftWalls;
				roomSprite = backBuffer->CreateSprite("assets\\twoDoorsTopLeftWallsOpen.png");
			}
			else if ((int)c == 54)
			{//6
				gm_room = twoDoorsTopRightWalls;
				roomSprite = backBuffer->CreateSprite("assets\\twoDoorsTopRightWallsOpen.png");
			}
			else if ((int)c == 55)
			{//7
				gm_room = twoDoorsBottomLeftWalls;
				roomSprite = backBuffer->CreateSprite("assets\\twoDoorsBottomLeftWallsOpen.png");
			}
			else if ((int)c == 56)
			{//8
				gm_room = twoDoorsBottomRightWalls;
				roomSprite = backBuffer->CreateSprite("assets\\twoDoorsBottomRightWallsOpen.png");
			}
			else if ((int)c == 57)
			{//9
				gm_room = twoDoorsSplitHorizontal;
				roomSprite = backBuffer->CreateSprite("assets\\twoDoorsSplitHorizontalOpen.png");
			}
			else if ((int)c == 97)
			{//a
				gm_room = twoDoorsSplitVertical;
				roomSprite = backBuffer->CreateSprite("assets\\twoDoorsSplitVerticalOpen.png");
			}
			else if ((int)c == 98)
			{//b
				gm_room = oneDoorAtBottom;
				roomSprite = backBuffer->CreateSprite("assets\\oneDoorAtBottomOpen.png");
			}
			else if ((int)c == 99)
			{//c
				gm_room = oneDoorAtTop;
				roomSprite = backBuffer->CreateSprite("assets\\oneDoorAtTopOpen.png");
			}
			else if ((int)c == 100)
			{//d
				gm_room = oneDoorOnRight;
				roomSprite = backBuffer->CreateSprite("assets\\oneDoorOnRightOpen.png");
			}
			else if ((int)c == 101)
			{//e
				gm_room = oneDoorOnLeft;
				roomSprite = backBuffer->CreateSprite("assets\\oneDoorOnLeftOpen.png");
			}
			//else if ((int)c == 101)
			//{//T for treasure
			//	gm_room = oneDoorOnLeft;
			//}
			//else if ((int)c == 101)
			//{//e
			//	gm_room = oneDoorOnLeft;
			//}
			//else if ((int)c == 101)
			//{//e
			//	gm_room = oneDoorOnLeft;
			//}
			else 
			{
				gm_room = blank;
				roomSprite = backBuffer->CreateSprite("assets\\Blank.png");
			}

			Room* room = new Room(j, i, gm_room);
			room->Initialise(roomSprite);
			//room->setRoomNumber(gm_room);
			gm_layout[j][i] = room;
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