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

	int getClient();
	void setClient(int client);

private:
	int clientID;
	int direction;
};

#endif