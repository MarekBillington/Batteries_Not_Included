#ifndef __BULLET_H__
#define __BULLET_H__

#include "entity.h"
#include "sprite.h"
#include <cmath>

class Bullet : public Entity
{
public:
	Bullet(int dir);
	~Bullet();

	int getDirection();
	void setDirection(int dir);

	int getClient();
	void setClient(int client);

	//bool IsCollidingWith(Entity& e);

private:

	//Sprite* m_pSprite;
	int clientID;
	int direction;
};

#endif