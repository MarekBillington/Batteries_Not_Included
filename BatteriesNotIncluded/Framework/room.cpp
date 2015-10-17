#include "room.h"


Room::Room()
{
}

Room::Room(int i, int j)
{
	m_x = i * 1280;
	m_y = j * 720;
	//could probably do this above but eh
}

Room::~Room()
{
}


void Room::setRoomNumber(int num){
	ro_roomNumber = num;
}

int Room::getRoomNumber(){
	return ro_roomNumber;
}