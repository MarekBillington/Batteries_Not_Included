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
			Sprite* lockedSprite;
			
			char c;
			mapfile >> c;
			RoomSpecial gm_roomType = NONE;
			////////////////////////////////////
			if ((int)c == 84)
			{//T for treasure
				gm_roomType = ITEM;
				mapfile >> c;
			}
			else if ((int)c == 83)
			{//S spawn
				gm_roomType = SPAWN;
				mapfile >> c;
			}
			else if ((int)c == 36)
			{//$ shop
				gm_roomType = SHOP;
				mapfile >> c;
			}
			else if ((int)c == 41)
			{//! boss
				gm_roomType = BOSSROOM;
				mapfile >> c;
			}
			else if ((int)c == 66)
			{//B boss entrance
				gm_roomType = BOSSENTERANCE;
				mapfile >> c;
			}
			///////////////////////////////////

			if ((int)c == 48)
			{//0
				gm_room = fourDoors;
				roomSprite = backBuffer->CreateSprite("assets\\AllDoorsOpenRoom.png");
				lockedSprite = backBuffer->CreateSprite("assets\\AllDoorsClosedRoom.png");
			}
			else if ((int)c == 49)
			{//1
				gm_room = threeDoorsTopWall;
				roomSprite = backBuffer->CreateSprite("assets\\threeDoorsTopWallOpen.png");
				lockedSprite = backBuffer->CreateSprite("assets\\threeDoorsTopWallClosed.png");
			}
			else if ((int)c == 50)
			{//2
				gm_room = threeDoorsBottomWall;
				roomSprite = backBuffer->CreateSprite("assets\\threeDoorsBottomWallOpen.png");
				lockedSprite = backBuffer->CreateSprite("assets\\threeDoorsBottomWallClosed.png");
			}
			else if ((int)c == 51)
			{//3
				gm_room = threeDoorsLeftWall;
				roomSprite = backBuffer->CreateSprite("assets\\threeDoorsLeftWallOpen.png");
				lockedSprite = backBuffer->CreateSprite("assets\\threeDoorsLeftWallClosed.png");
			}
			else if ((int)c == 52)
			{//4
				gm_room = threeDoorsRightWall;
				roomSprite = backBuffer->CreateSprite("assets\\threeDoorsRightWallOpen.png");
				lockedSprite = backBuffer->CreateSprite("assets\\threeDoorsRightWallClosed.png");
			}
			else if ((int)c == 53)
			{//5
				gm_room = twoDoorsTopLeftWalls;
				roomSprite = backBuffer->CreateSprite("assets\\twoDoorsTopLeftWallsOpen.png");
				lockedSprite = backBuffer->CreateSprite("assets\\twoDoorsTopLeftWallsClosed.png");
			}
			else if ((int)c == 54)
			{//6
				gm_room = twoDoorsTopRightWalls;
				roomSprite = backBuffer->CreateSprite("assets\\twoDoorsTopRightWallsOpen.png");
				lockedSprite = backBuffer->CreateSprite("assets\\twoDoorsTopRightWallsClosed.png");
			}
			else if ((int)c == 55)
			{//7
				gm_room = twoDoorsBottomLeftWalls;
				roomSprite = backBuffer->CreateSprite("assets\\twoDoorsBottomLeftWallsOpen.png");
				lockedSprite = backBuffer->CreateSprite("assets\\twoDoorsBottomLeftWallsClosed.png");
			}
			else if ((int)c == 56)
			{//8
				gm_room = twoDoorsBottomRightWalls;
				roomSprite = backBuffer->CreateSprite("assets\\twoDoorsBottomRightWallsOpen.png");
				lockedSprite = backBuffer->CreateSprite("assets\\twoDoorsBottomRightWallsClosed.png");
			}
			else if ((int)c == 57)
			{//9
				gm_room = twoDoorsSplitHorizontal;
				roomSprite = backBuffer->CreateSprite("assets\\twoDoorsSplitHorizontalOpen.png");
				lockedSprite = backBuffer->CreateSprite("assets\\twoDoorsSplitHorizontalClosed.png");
			}
			else if ((int)c == 97)
			{//a
				gm_room = twoDoorsSplitVertical;
				roomSprite = backBuffer->CreateSprite("assets\\twoDoorsSplitVerticalOpen.png");
				lockedSprite = backBuffer->CreateSprite("assets\\twoDoorsSplitVerticalClosed.png");
			}
			else if ((int)c == 98)
			{//b
				gm_room = oneDoorAtBottom;
				roomSprite = backBuffer->CreateSprite("assets\\oneDoorAtBottomOpen.png");
				lockedSprite = backBuffer->CreateSprite("assets\\oneDoorAtBottomClosed.png");
			}
			else if ((int)c == 99)
			{//c
				gm_room = oneDoorAtTop;
				roomSprite = backBuffer->CreateSprite("assets\\oneDoorAtTopOpen.png");
				lockedSprite = backBuffer->CreateSprite("assets\\oneDoorAtTopClosed.png");
			}
			else if ((int)c == 100)
			{//d
				gm_room = oneDoorOnRight;
				roomSprite = backBuffer->CreateSprite("assets\\oneDoorOnRightOpen.png");
				lockedSprite = backBuffer->CreateSprite("assets\\oneDoorOnRightClosed.png");
			}
			else if ((int)c == 101)
			{//e
				gm_room = oneDoorOnLeft;
				roomSprite = backBuffer->CreateSprite("assets\\oneDoorOnLeftOpen.png");
				lockedSprite = backBuffer->CreateSprite("assets\\oneDoorOnLeftClosed.png");
			}
			else 
			{
				gm_room = blank;
				roomSprite = backBuffer->CreateSprite("assets\\Blank.png");
				lockedSprite = backBuffer->CreateSprite("assets\\Blank.png");

			}

			Room* room = new Room(j, i, gm_room, gm_roomType);
			room->Initialise(roomSprite);
			room->ro_lockedSprite = lockedSprite;
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