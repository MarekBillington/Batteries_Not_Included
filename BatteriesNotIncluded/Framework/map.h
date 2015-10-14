//Creates the map and governs the timers for the specific rooms
#ifndef __MAP_H__
#define __MAP_H__

class BackBuffer;
class Sprite;

enum Room
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

class Map
{
public:
	Map();
	~Map();

	void parseFile();

	Room getRoom();
	void setRoom(Room room);

	bool initialise(Sprite* sprite);
	void process(float deltaTime);
	void drawRoom(BackBuffer& backbuffer);

	int getItemTimer();
	void setItemTimer(int itemTimer);
	int getBossTimer();
	void setBossTimer(int bossTimer);

	bool arePlayersDuelling();

	bool isItemRoomActive();

	bool isBossRoomActive();

private:
	Room ma_layout[9][9];
	Room ma_room;
	int ma_itemTimer;
	int ma_bossTimer;
	bool ma_playerDuel;
	bool ma_itemActivate;
	bool ma_bossActivate;
};

#endif