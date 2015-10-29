#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "entity.h"
#include "weapon.h"
#include "passive.h"
#include "active.h"
#include "sprite.h"
#include "animatedsprite.h"


#include <string>


class Player : public Entity
{
public:
	Player();
	~Player();



	//Processing
	bool Initialise(AnimatedSprite* sprite);
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	//Name
	std::string getName();
	void setName(std::string name);

	//Stats

	/*int getCurrentRoomX();	//- moved to entity
	int getCurrentRoomY();*/
	//int getHealth();
	int getAttackSpeed();
	int getAttackDamage();
	int getMovementSpeed();

	/*void setCurrentRoomX(int x);	//- moved to entity
	void setCurrentRoomY(int y);*/
	//void setHealth(int health);
	void getAttackSpeed(int attackSpeed);
	void getAttackDamage(int attackDamage);
	void setMovementSpeed(int movementSpeed);
	void setDirection(int direction);

	//Items
	Weapon* getWeapon();
	Passive* getPassive(int passiveNum);
	Active* getActive();

	void setWeapon(Weapon* weapon);
	void setPassive(int passiveNum, Passive* passive);
	void setActive(Active* active);

	//Effects
	int fireTimeRemaining();
	int poisonedTimeRemaining();
	int electrocutedTimeRemaining();
	int repairingTimeRemaining();

	void setOnFire(int duration);
	void setPoisoned(int duration);
	void setElectrocuted(int duration);
	void setRepairing(int duration);

	int getWidth();
	int getHeight();
	bool isPlayer();
	//AnimatedSprite* getSprite();

private:
	AnimatedSprite* m_pSprite;

	std::string  pl_name;

	/*int pl_currentRoomX;	- moved to entity
	int pl_currentRoomY;*/

	//int pl_health;
	int pl_attackSpeed;
	int pl_attackDamage;
	int pl_movementSpeed;
	int pl_direction;

	Weapon* pl_weapon;

	Passive* pl_passive1;
	Passive* pl_passive2;
	Passive* pl_passive3;
	Passive* pl_passive4;

	Active* pl_active;


	int pl_remainingDurationPoisoned;
	int pl_remainingDurationFire;
	int pl_remainingDurationElectrocuted;
	int pl_remainingDurationRepairing;


};

#endif // !__PLAYER_H__
