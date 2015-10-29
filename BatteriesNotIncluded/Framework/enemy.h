#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "entity.h"
#include "weapon.h"
#include "passive.h"
#include "active.h"
#include "sprite.h"

#include <string>

enum EnemyType
{
	UNDEFINED,
	ROBORAT,
	ROBOSCORPIONDOG,
	TIGERS,
	GRUNT,
	SCRAPSHOOTER,
	BOSS
};

enum EnemyState{
	PASSIVE,
	AGRO,
	HIDING
};

class Enemy : public Entity
{
public:
	Enemy(EnemyType enemyType, int x, int y, BackBuffer* backBuffer);
	~Enemy();


	//Processing
	bool Initialise(Sprite* sprite);
	void Process(float deltaTime);
	//void Draw(BackBuffer& backBuffer);

	//stats
	int getCurrentRoomX();
	int getCurrentRoomY();
	int getHealth();
	int getAttackSpeed();
	int getAttackDamage();
	int getMovementSpeed();

	void setHealth(int health);
	void getAttackSpeed(int attackSpeed);
	void getAttackDamage(int attackDamage);
	void setMovementSpeed(int movementSpeed);
	void setInitialStats();
	void setInitialRoboratStats();
	void setInitialRoboscorpiondogStats();
	void setInitialTigerStats();
	void setInitialGruntStats();
	void setInitialScrapshooterStats();
	void setInitialBossStats();

	void roboratProcess();
	void roboscorpiondogProcess();
	void tigerProcess();
	void gruntProcess();
	void scrapshooterProcess();
	void bossProcess();


	//items not moved from player.h

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
	//name not included
	EnemyType en_enemyType;
	EnemyState en_enemyState;
	int en_currentRoomX;
	int en_currentRoomY;

	int en_health;
	int en_attackSpeed;
	int en_attackDamage;
	int en_movementSpeed;

	//weapon + passive + active not included

	int en_remainingDurationPoisoned;
	int en_remainingDurationFire;
	int en_remainingDurationElectrocuted;
	int en_remainingDurationRepairing;

};

#endif // !__ENEMY_H__

