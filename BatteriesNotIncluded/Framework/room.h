#ifndef __ROOM_H__
#define __ROOM_H__

#include "entity.h"
#include "terrain.h"
#include "wall.h"
#include <vector>

enum RoomType
{
	fourDoors,
	threeDoorsTopWall,
	threeDoorsBottomWall,
	threeDoorsLeftWall,
	threeDoorsRightWall,
	twoDoorsTopLeftWalls,
	twoDoorsTopRightWalls,
	twoDoorsBottomLeftWalls,
	twoDoorsBottomRightWalls,
	twoDoorsSplitHorizontal,
	twoDoorsSplitVertical,
	oneDoorAtBottom,
	oneDoorAtTop,
	oneDoorOnRight,
	oneDoorOnLeft,
	blank
};



class Room: public Entity
{
public:
	Room();
	Room(int i, int j, RoomType type);
	~Room();

	void setRoomNumber(RoomType num);
	int getRoomNumber();
	void createTerrain(RoomType type);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	bool IsCollidingWith(Entity& e);

<<<<<<< HEAD
	RoomType getRoomType();
=======
	void createWall(int x, int y, int width, int height, Side side);

>>>>>>> 380c5c16e3ea1fa226d337c14d2526416f74f16c
private:
	RoomType ro_roomNumber;

	std::vector<Terrain*> ro_terrainContainer;
	std::vector<Wall*> ro_wallContainer;
	//std::vector<Enemy*> enemyContainer;
};


#endif // !__ROOM_H__
