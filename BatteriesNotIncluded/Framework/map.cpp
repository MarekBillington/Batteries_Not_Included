//Map class

#include "map.h"
#include <fstream>

Map::Map()
: ma_bossTimer(0)
, ma_itemTimer(0)
, ma_layout()
, ma_room()
, ma_bossActivate()
, ma_itemActivate()
, ma_playerDuel()
{

}

Map::~Map()
{

}

void
Map::parseFile()
{
	BackBuffer* backbuffer;
	ma_layout[9][9];
	std::ifstream mapfile;
	mapfile.open("assets\\map_1.txt");

	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			Sprite* sprite;
			char c;
			mapfile >> c;
			if ((int)c == 48)
			{
				Room ma_room = fourDoors;
				ma_layout[i][j] = ma_room;
				//sprite = backbuffer->CreateSprite("");
			}
			if ((int)c == 49)
			{
				Room ma_room = threeDoorsTopWall;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 50)
			{
				Room ma_room = threeDoorsBottomWall;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 51)
			{
				Room ma_room = threeDoorsLeftWall;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 52)
			{
				Room ma_room = threeDoorsRightWall;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 53)
			{
				Room ma_room = twoDoorsTopLeftWalls;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 54)
			{
				Room ma_room = twoDoorsTopRightWalls;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 55)
			{
				Room ma_room = twoDoorsBottomLeftWalls;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 56)
			{
				Room ma_room = twoDoorsBottomRightWalls;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 57)
			{
				Room ma_room = twoDoorsSplitHorizontal;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 97)
			{
				Room ma_room = twoDoorsSplitVertical;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 98)
			{
				Room ma_room = oneDoorAtBottom;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 99)
			{
				Room ma_room = oneDoorAtTop;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 100)
			{
				Room ma_room = oneDoorOnRight;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 101)
			{
				Room ma_room = oneDoorOnLeft;
				ma_layout[i][j] = ma_room;
			}
			if ((int)c == 102)
			{
				Room ma_room = blank;
				ma_layout[i][j] = ma_room;
			}
		}
	}
}