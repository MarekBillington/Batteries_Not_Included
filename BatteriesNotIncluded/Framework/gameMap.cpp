#include "gameMap.h"
#include "room.h"
#include <fstream>

GameMap::GameMap()
{
}

GameMap::~GameMap()
{
}


void
GameMap::parseFile()
{
	
	ma_layout[9][9];
	std::ifstream mapfile;
	mapfile.open("assets\\map_2.txt");

	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			Room* room = new Room();

			char c;
			mapfile >> c;
			if ((int)c == 48)
			{
				ma_room = fourDoors;
			}
			else if ((int)c == 49)
			{
				ma_room = threeDoorsTopWall;
			}
			else if ((int)c == 50)
			{
				ma_room = threeDoorsBottomWall;
			}
			else if ((int)c == 51)
			{
				ma_room = threeDoorsLeftWall;
			}
			else if ((int)c == 52)
			{
				ma_room = threeDoorsRightWall;
			}
			else if ((int)c == 53)
			{
				ma_room = twoDoorsTopLeftWalls;
			}
			else if ((int)c == 54)
			{
				 ma_room = twoDoorsTopRightWalls;
			}
			else if ((int)c == 55)
			{
				ma_room = twoDoorsBottomLeftWalls;
			}
			else if ((int)c == 56)
			{
				ma_room = twoDoorsBottomRightWalls;
			}
			else if ((int)c == 57)
			{
				 ma_room = twoDoorsSplitHorizontal;
			}
			else if ((int)c == 97)
			{
				ma_room = twoDoorsSplitVertical;
			}
			else if ((int)c == 98)
			{
				ma_room = oneDoorAtBottom;
			}
			else if ((int)c == 99)
			{
				ma_room = oneDoorAtTop;
			}
			else if ((int)c == 100)
			{
				ma_room = oneDoorOnRight;
			}
			else if ((int)c == 101)
			{
				ma_room = oneDoorOnLeft;
			}
			else 
			{
				ma_room = blank;
			}
			room->setRoomNumber(ma_room);
			ma_layout[i][j] = room;
		}
	}
}

int
GameMap::getNumItemAt(int i, int j){
	return ma_layout[i][j]->getRoomNumber();
}

void
GameMap::setNumItemAt(int i, int j, Rooms value){
	ma_layout[i][j]->setRoomNumber(value);
}