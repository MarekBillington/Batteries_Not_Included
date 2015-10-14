
#include"player.h"

Player::Player()
{
}



Player::~Player()
{
}


bool
Player::Initialise(Sprite* sprite)
{
	m_pSprite = sprite;

	return (true);
}

void
Player::Process(float deltaTime)
{
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));

}

void
Player::Draw(BackBuffer& backBuffer)
{
	m_pSprite->Draw(backBuffer);
}


float Player::getHealth(){
	return pl_health;
}
void Player::setHealth(float health){
	pl_health = health;
}

float Player::getAttackSpeed(){
	return pl_attackSpeed;
}
void Player::getAttackSpeed(float attackSpeed){
	pl_attackSpeed = attackSpeed;
}
float Player::getAttackDamage(){
	return pl_attackDamage;
}
void Player::getAttackDamage(float attackDamage){
	pl_attackDamage = attackDamage;
}
float Player::getMovementSpeed(){
	return pl_movementSpeed;
}
void Player::setMovementSpeed(float movementSpeed){
	pl_movementSpeed = movementSpeed;
}



Weapon Player::getWeapon(){
	return pl_weapon;
}
void Player::setWeapon(Weapon weapon){
	pl_weapon = weapon;
}

Passive Player::getPassive(int passiveNum){
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
void Player::setPassive(int passiveNum, Passive passive){
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

Active Player::getActive(){
	return pl_active;
}
void Player::setActive(Active active){
	pl_active = active;
}

std::string Player::getName(){
	return pl_name;
}
void Player::setName(std::string name){
	pl_name = name;
}


int Player::fireTimeRemaining(){
	return pl_remainingDurationFire;
}
int Player::poisonedTimeRemaining(){
	return pl_remainingDurationPoisoned;
}
int Player::electrocutedTimeRemaining(){
	return pl_remainingDurationElectrocuted;
}
int Player::repairingTimeRemaining(){
	return pl_remainingDurationRepairing;
}

void Player::setOnFire(int duration){
	pl_remainingDurationFire = duration;

}
void Player::setPoisoned(int duration){
	pl_remainingDurationPoisoned = duration;
}
void Player::setElectrocuted(int duration){
	pl_remainingDurationElectrocuted = duration;
}
void Player::setRepairing(int duration){
	pl_remainingDurationRepairing = duration;
}
