// 717310 C++ SDL Framework

// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "backbuffer.h"

// Library includes:
#include <cassert>

Entity::Entity()
	: m_pSprite(0)
	, m_x(0.0f)
	, m_y(0.0f)
	, m_velocityX(0.0f)
	, m_velocityY(0.0f)
	, m_dead(false)
	, en_health(0)
	, en_currentRoomX(0)
	, en_currentRoomY(0)
{

}

Entity::~Entity()
{

}

bool
Entity::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
	return (true);
}

void 
Entity::Process(float deltaTime)
{
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));

	// Ex006.2: Generic position update, based upon velocity (and time).

	// Ex006.2: Boundary checking and position capping. 
}

void 
Entity::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->Draw(backBuffer);
}

bool
Entity::IsCollidingWith(Entity& e)
{
	// Ex006.4: Generic Entity Collision routine.

	// Ex006.4: Does this object collide with the e object?
	// Ex006.4: Create a circle for each entity (this and e).

	// Ex006.4: Check for intersection.
	// Ex006.4: Using circle-vs-circle collision detection.

	// Ex006.4: Return result of collision.

	return (false); // Ex006.4 Change return value!
}

void 
Entity::SetDead(bool dead)
{
	m_dead = dead;
}

float 
Entity::GetPositionX()
{
	return (m_x);
}

float 
Entity::GetPositionY()
{
	return (m_y);
}

void
Entity::SetPositionX(float x)
{
	m_x = x;
}

void
Entity::SetPositionY(float y)
{
	m_y = y;
}


int 
Entity::getCurrentRoomX(){
	return en_currentRoomX;
}

int 
Entity::getCurrentRoomY(){
	return en_currentRoomY;
}

void 
Entity::setCurrentRoomX(int x){
	en_currentRoomX = x;
}

void 
Entity::setCurrentRoomY(int y){
	en_currentRoomY = y;
}



float 
Entity::GetHorizontalVelocity()
{
	return (m_velocityX);
}

float 
Entity::GetVerticalVelocity()
{
	return (m_velocityY);
}

void 
Entity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void 
Entity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}

Sprite* 
Entity::getSprite(){
	return m_pSprite;
}


bool
Entity::isPlayer(){
	return false;
}

int
Entity::getWidth(){
	return en_width;
}

int
Entity::getHeight(){
	return en_height;
}


void
Entity::setWidth(int w){
	en_width = w;
}

void
Entity::setHeight(int h){
	en_height = h;
}



int
Entity::getHealth(){
	return en_health;
}

void
Entity::setHealth(int health){
	//if (en_health - health < 1){
		//en_health = 0;
		//SetDead(true);
	//}
	//else{
		en_health = health;
	//}	
	
}
