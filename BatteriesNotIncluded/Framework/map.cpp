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
	std::ifstream mapfile;
	mapfile.open("assets\\map_1.txt");

	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			char c;
			mapfile >> c;
			if (true)
			{
				//get number from file
				//create Room var and set as room type
			}
		}
	}
}