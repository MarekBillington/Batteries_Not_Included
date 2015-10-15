#ifndef __ROOM_H__
#define __ROOM_H__

#include "entity.h"


class Room: public Entity
{
public:
	Room();
	~Room();

	void setRoomNumber(int num);
	int getRoomNumber();

private:
	int ro_roomNumber;
};


#endif // !__ROOM_H__
