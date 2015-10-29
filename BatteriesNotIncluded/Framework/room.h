#ifndef __ROOM_H__
#define __ROOM_H__

#include "entity.h"
#include "terrain.h"
#include "wall.h"
#include "enemy.h"
#include <vector>
#include "sprite.h"
#include "texture.h"

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

enum RoomSpecial
{
	NONE,
	SPAWN,
	ITEM,
	SHOP,
	BOSSROOM,
	BOSSENTERANCE
};

class Room: public Entity
{
public:
	Room();
	Room(int i, int j, RoomType type, RoomSpecial special);
	~Room();

	void setRoomNumber(RoomType num);
	int getRoomNumber();
	void createTerrain(RoomType type);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	bool IsCollidingWith(Entity& e);
	RoomType getRoomType();
	void createWall(int x, int y, int width, int height, Side side, bool door, bool open);

	RoomSpecial getRoomSpecial();
	bool ro_Locked = false;
private:
	

	RoomType ro_roomNumber;
	RoomSpecial ro_roomSpecial;

	std::vector<Terrain*> ro_terrainContainer;
	std::vector<Wall*> ro_wallContainer;
	std::vector<Enemy*> ro_enemyContainer;

	bool ro_doorNorth;
	bool ro_doorEast;
	bool ro_doorSouth;
	bool ro_doorWest;


};


#endif // !__ROOM_H__
