#include "bullet.h"
#include "game.h"
#include "backbuffer.h"

Bullet::Bullet(int dir)
{
	direction = dir;


	
}

Bullet::~Bullet()
{

}


int
Bullet::getDirection()
{
	return direction;
}

void
Bullet::setDirection(int dir)
{
	direction = dir;
}

int
Bullet::getClient()
{
	return direction;
}

void
Bullet::setClient(int cl)
{
	clientID = cl;
}
