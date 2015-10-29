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
	RoomType getRoomType();
	void createWall(int x, int y, int width, int height, Side side);

private:
	RoomType ro_roomNumber;

	std::vector<Terrain*> ro_terrainContainer;
	std::vector<Wall*> ro_wallContainer;
	//std::vector<Enemy*> enemyContainer;
};


#endif // !__ROOM_H__
