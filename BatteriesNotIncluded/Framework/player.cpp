
#include"player.h"
#include "backbuffer.h"

#include <cassert>

Player::Player()
	:pl_direction(0)
	, pl_deathCount(0)
	
{
	setHealth(1000);
}



Player::~Player()
{
}


bool
Player::Initialise(AnimatedSprite* sprite)
{
	int length = 0;
	while (length < 2){
		length++;
		sprite->AddFrame(length);
	}

	sprite->SetFrameSpeed(0.3);
	sprite->SetFrameWidth(114.0);
	setWidth(114);
	sprite->SetHeight(112.0);
	setHeight(112);

	assert(sprite);
	m_pSprite = sprite;

	return (true);
}

void
Player::Process(float deltaTime)
{
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
	m_pSprite->setLocation(pl_direction);
	m_x += m_velocityX*deltaTime;
	m_y += m_velocityY*deltaTime;
	
	if (m_velocityX == 0 && m_velocityY == 0)
	{
		m_pSprite->SetFrameSpeed(50.0);
	}
	else
	{
		m_pSprite->SetFrameSpeed(0.3);
	}

	if (m_velocityX < 0)
	{
		pl_direction = 1;
	}
	else if (m_velocityX > 0)
	{
		pl_direction = 2;
	}

	if (m_velocityY < 0)
	{
		pl_direction = 3;
	}
	else if (m_velocityY > 0)
	{
		pl_direction = 0;
	}

	m_pSprite->Process(deltaTime);

	en_currentRoomX = (m_x / 1280);
	en_currentRoomY = (m_y / 720);

}

void
Player::Draw(BackBuffer& backBuffer, std::string name)
{
	Sprite* nameTXT = backBuffer.CreateText(name, { 255, 255, 255, 150 }, "assets//dkjalebi.otf", 20);
	nameTXT->SetX(m_pSprite->GetX());
	nameTXT->SetY(m_pSprite->GetY()-25);
	backBuffer.DrawSprite(*nameTXT);

	assert(m_pSprite);
	m_pSprite->Draw(backBuffer);
}


//int 
//Player::getCurrentRoomX(){
//	return pl_currentRoomX;
//}
//
//int 
//Player::getCurrentRoomY(){
//	return pl_currentRoomY;
//}
//
//void 
//Player::setCurrentRoomX(int x){
//	pl_currentRoomX = x;
//}
//
//void 
//Player::setCurrentRoomY(int y){
//	pl_currentRoomY = y;
//}
//
////
////int 
////Player::getHealth(){
////	return pl_health;
////}
////
////void 
////Player::setHealth(int health){
////	pl_health = health;
////}

int 
Player::getAttackSpeed(){
	return pl_attackSpeed;
}

void 
Player::getAttackSpeed(int attackSpeed){
	pl_attackSpeed = attackSpeed;
}

int 
Player::getAttackDamage(){
	return pl_attackDamage;
}

void 
Player::getAttackDamage(int attackDamage){
	pl_attackDamage = attackDamage;
}

int 
Player::getMovementSpeed(){
	return pl_movementSpeed;
}

void 
Player::setMovementSpeed(int movementSpeed){
	pl_movementSpeed = movementSpeed;
}

void
Player::setDirection(int direction)
{
	pl_direction = direction;
}



Weapon* 
Player::getWeapon(){
	return pl_weapon;
}

void 
Player::setWeapon(Weapon* weapon){
	pl_weapon = weapon;
}

Passive* 
Player::getPassive(int passiveNum){
	if (passiveNum == 1){
		return pl_passive1;
	}
	else if (passiveNum == 2){
		return pl_passive2;
	}
	else if (passiveNum == 3){
		return pl_passive3;
	}
	else {
		return pl_passive4;
	}
}

void 
Player::setPassive(int passiveNum, Passive* passive){
	if (passiveNum == 1){
		pl_passive1 = passive;
	}
	else if (passiveNum == 2){
		pl_passive2 = passive;
	}
	else if (passiveNum == 3){
		pl_passive3 = passive;
	}
	else {
		pl_passive4 = passive;
	}
}

Active* 
Player::getActive(){
	return pl_active;
}

void 
Player::setActive(Active* active){
	pl_active = active;
}

std::string 
Player::getName(){
	return pl_name;
}

void 
Player::setName(std::string name){
	pl_name = name;
}

int 
Player::fireTimeRemaining(){
	return pl_remainingDurationFire;
}

int 
Player::poisonedTimeRemaining(){
	return pl_remainingDurationPoisoned;
}

int 
Player::electrocutedTimeRemaining(){
	return pl_remainingDurationElectrocuted;
}

int 
Player::repairingTimeRemaining(){
	return pl_remainingDurationRepairing;
}

void 
Player::setOnFire(int duration){
	pl_remainingDurationFire = duration;

}

void 
Player::setPoisoned(int duration){
	pl_remainingDurationPoisoned = duration;
}

void 
Player::setElectrocuted(int duration){
	pl_remainingDurationElectrocuted = duration;
}

void 
Player::setRepairing(int duration){
	pl_remainingDurationRepairing = duration;
}


int
Player::getWidth(){
	return en_height;
}

int
Player::getHeight(){
	return en_height;
}

bool
Player::isPlayer(){
	return true;
}