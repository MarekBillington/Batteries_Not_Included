#ifndef __WALL_H__
#define __WALL_H__

#include "entity.h"


class Wall : public Entity
{
public:
	Wall(int x, int y, int x1, int y1);
	~Wall();

	void setWallX(int x);
	int getWallX();

	void setWallY(int y);
	int getWallY();

	void setWallX1(int x);
	int getWallX1();

	void setWallY1(int y);
	int getWallY1();


private:
	int wa_X;
	int wa_Y;
	int wa_X1;
	int wa_Y1;
};


#endif // !__ROOM_H__
