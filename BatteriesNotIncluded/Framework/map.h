//Creates the map and governs the timers for the specific rooms
#ifndef __MAP_H__
#define __MAP_H__

class BackBuffer;
class Sprite;

enum Rooms
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

	Rooms getRoom();
	void setRoom(Rooms room);

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

	int getNumItemAt(int i, int j);
	void setNumItemAt(int i, int j, Rooms value);

private:
	Rooms ma_layout[9][9];
	Rooms ma_room;
	int ma_itemTimer;
	int ma_bossTimer;
	bool ma_playerDuel;
	bool ma_itemActivate;
	bool ma_bossActivate;
};

#endif