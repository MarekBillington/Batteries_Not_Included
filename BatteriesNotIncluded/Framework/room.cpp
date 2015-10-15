#include "room.h"


Room::Room()
{
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