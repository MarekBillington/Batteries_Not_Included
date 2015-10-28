#include "wall.h"


Wall::Wall(int x, int y, int x1, int y1)
{
	wa_X = x;
	wa_Y = y;
	wa_X1 = x1;
	wa_Y1 = y1;
}

Wall::~Wall()
{
}


void Wall::setWallX(int num){
	wa_X = num;
}

void Wall::setWallY(int num){
	wa_Y = num;
}

int Wall::getWallX(){
	return wa_X;
}

int Wall::getWallY(){
	return wa_Y;
}

void Wall::setWallX1(int num){
	wa_X1 = num;
}

void Wall::setWallY1(int num){
	wa_Y1 = num;
}

int Wall::getWallX1(){
	return wa_X1;
}

int Wall::getWallY1(){
	return wa_Y1;
}
