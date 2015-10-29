#ifndef __WALL_H__
#define __WALL_H__

#include "entity.h"
#include "sprite.h"

enum Side
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

class Wall
{
public:
	Wall(int x, int y, int width, int height, Side side, bool door, bool wa_open);
	~Wall();

	bool IsCollidingWith(Entity& e, bool lockdown);
	int getX();
	int getY();
	int getWidth();
	int getHeight();

private:
	
	int wa_xloc;
	int wa_yloc;
	int wa_width;
	int wa_height;
	Side wa_side;
	bool wa_door;
	bool wa_open;
};



#endif // !__WALL_H__
