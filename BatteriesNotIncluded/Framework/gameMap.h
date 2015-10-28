#ifndef __GAMEMAP_H__
#define __GAMEMAP_H__


class BackBuffer;
class Sprite;
#include "room.h"


class GameMap
{
public:
	GameMap(BackBuffer* backbuffer);
	~GameMap();

	void parseFile();

	void process(float deltaTime);
	void draw(BackBuffer& backbuffer);

	Room* getRoomAt(int i, int j);
	void setRoomAt(int i, int j, Room* value);

	Sprite* BottomWallDoor;
	Sprite* TopWallDoor;
	Sprite* RightWallDoor;
	Sprite* LeftWallDoor;

	Sprite* BottomWallNoDoor;
	Sprite* TopWallNoDoor;
	Sprite* RightWallNoDoor;
	Sprite* LeftWallNoDoor;


private:
	Room* gm_layout[9][9];
	RoomType gm_room;

};



#endif // !__GAMEMAP_H__
