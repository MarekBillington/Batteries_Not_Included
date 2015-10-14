//Creates the map and governs the timers for the specific rooms
#ifndef __MAP_H__
#define __MAP_H__

class Map
{
public:
	Map();
	~Map();

	void parseFile();

	int getRoom();
	void setRoom();

	int getItemTimer();

	int getBossTimer();

	bool arePlayersDuelling();

	bool isItemRoomActive();

	bool isBossRoomActive();

private:
	int ma_layout[9][9];
	int ma_room;
	int ma_itemTimer;
	int ma_bossTimer;

};

#endif