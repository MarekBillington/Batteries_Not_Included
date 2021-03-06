#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "entity.h"
#include "weapon.h"
#include "passive.h"
#include "active.h"
#include "sprite.h"


#include <string>


class Player	: public Entity
{
public:
	Player();
	~Player();



	//Processing
	bool Initialise(Sprite* sprite);
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	//Name
	std::string getName();
	void setName(std::string name);

	//Stats
	float getHealth();
	float getAttackSpeed();
	float getAttackDamage();
	float getMovementSpeed();

	void setHealth(float health);
	void getAttackSpeed(float attackSpeed);
	void getAttackDamage(float attackDamage);
	void setMovementSpeed(float movementSpeed);

	//Items
	Weapon getWeapon();
	Passive getPassive(int passiveNum);
	Active getActive();

	void setWeapon(Weapon weapon);
	void setPassive(int passiveNum, Passive passive);
	void setActive(Active active);
	
	//Effects
	int fireTimeRemaining();
	int poisonedTimeRemaining();
	int electrocutedTimeRemaining();
	int repairingTimeRemaining();

	void setOnFire(int duration);
	void setPoisoned(int duration);
	void setElectrocuted(int duration);
	void setRepairing(int duration);



private:
	std::string  pl_name;

	int pl_health;
	int pl_attackSpeed;
	int pl_attackDamage;
	int pl_movementSpeed;

	Weapon pl_weapon;

	Passive pl_passive1;
	Passive pl_passive2;
	Passive pl_passive3;
	Passive pl_passive4;

	Active pl_active;

	
	int pl_remainingDurationPoisoned;
	int pl_remainingDurationFire;
	int pl_remainingDurationElectrocuted;
	int pl_remainingDurationRepairing;
	


};

#endif // !__PLAYER_H__
