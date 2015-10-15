//Map class

#include "map.h"
#include <fstream>

Map::Map()
: ma_bossTimer(0)
, ma_itemTimer(0)
, ma_room(fourDoors)
, ma_bossActivate(false)
, ma_itemActivate(false)
, ma_playerDuel(false)
//, ma_layout()
{
	parseFile();
}

Map::~Map()
{

}

void
Map::parseFile()
{
	//BackBuffer* backbuffer;
	ma_layout[9][9];
	std::ifstream mapfile;
	mapfile.open("assets\\map_2.txt");

	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			//Sprite* sprite;
			char c;
			mapfile >> c;
			if ((int)c == 48)
			{
				Rooms ma_room = fourDoors;
				ma_layout[i][j] = ma_room;
				//sprite = backbuffer->CreateSprite("");
			}
			if ((int)c == 49)
			{
				Rooms ma_room = threeDoorsTopWall;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 50)
			{
				Rooms ma_room = threeDoorsBottomWall;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 51)
			{
				Rooms ma_room = threeDoorsLeftWall;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 52)
			{
				Rooms ma_room = threeDoorsRightWall;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 53)
			{
				Rooms ma_room = twoDoorsTopLeftWalls;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 54)
			{
				Rooms ma_room = twoDoorsTopRightWalls;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 55)
			{
				Rooms ma_room = twoDoorsBottomLeftWalls;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 56)
			{
				Rooms ma_room = twoDoorsBottomRightWalls;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 57)
			{
				Rooms ma_room = twoDoorsSplitHorizontal;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 97)
			{
				Rooms ma_room = twoDoorsSplitVertical;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 98)
			{
				Rooms ma_room = oneDoorAtBottom;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 99)
			{
				Rooms ma_room = oneDoorAtTop;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 100)
			{
				Rooms ma_room = oneDoorOnRight;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 101)
			{
				Rooms ma_room = oneDoorOnLeft;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 102)
			{
				Rooms ma_room = blank;
				ma_layout[i][j] = ma_room;
			}
		}
	}
}

int 
Map::getNumItemAt(int i, int j){
	return ma_layout[i][j];
}

void 
Map::setNumItemAt(int i, int j, Rooms value){
	ma_layout[i][j] = value;
}