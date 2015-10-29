#include "bullet.h"

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