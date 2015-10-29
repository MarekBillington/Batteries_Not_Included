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
	Wall(int x, int y, int width, int height, Side side);
	~Wall();

	bool IsCollidingWith(Entity& e);
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

};



#endif // !__WALL_H__