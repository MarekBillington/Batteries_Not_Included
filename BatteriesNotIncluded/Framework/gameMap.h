#ifndef __GAMEMAP_H__
#define __GAMEMAP_H__


class BackBuffer;
class Sprite;
class Room;

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


class GameMap
{
public:
	GameMap();
	~GameMap();

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
	Room* ma_layout[9][9];
	Rooms ma_room;
	int ma_itemTimer;
	int ma_bossTimer;
	bool ma_playerDuel;
	bool ma_itemActivate;
	bool ma_bossActivate;
};



#endif // !__GAMEMAP_H__
