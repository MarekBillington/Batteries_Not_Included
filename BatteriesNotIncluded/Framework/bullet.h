#ifndef __BULLET_H__
#define __BULLET_H__

#include "entity.h"

class Bullet : public Entity
{
public:
	Bullet(int dir);
	~Bullet();

	int getDirection();
	void setDirection(int dir);

private:

	int direction;
};

#endif