#include "enemy.h"
#include "backbuffer.h"

Enemy::Enemy(EnemyType enemyType, int x, int y, BackBuffer* backBuffer)
{
	SetPositionX(x);
	SetPositionY(y);

	AnimatedSprite* enemySprite;

	if (enemyType == ROBORAT){
		enemySprite = backBuffer->CreateAnimatedSprite("assets\\alienenemy.png");
	}
	if (enemyType == BOSS){
		enemySprite = backBuffer->CreateAnimatedSprite("assets\\boss 280.png");
		SetHorizontalVelocity(-100);
	}
	
	en_enemyType = enemyType;
	en_enemyState = PASSIVE;
	Initialise(enemySprite);
	setInitialStats();
}

Enemy::~Enemy()
{

}

bool
Enemy::Initialise(AnimatedSprite* pSprite)
{
	en_pSprite = pSprite;
	int length = 0;
	while (length < 7){
		length++;
		en_pSprite->AddFrame(length);
	}

	en_pSprite->SetFrameSpeed(0.3);
	en_pSprite->SetFrameWidth(280.0);
	setWidth(280.0);
	en_pSprite->SetHeight(340);
	setHeight(340);
	


	return (true);
}


void
Enemy::Draw(BackBuffer& backBuffer)
{
	if (en_health <= 0){

	}
	else {
		en_pSprite->Draw(backBuffer);
	}
}

void
Enemy::Process(float deltaTime)
{
	en_pSprite->SetX(static_cast<int>(m_x));
	en_pSprite->SetY(static_cast<int>(m_y));

	m_x += m_velocityX*deltaTime;
	m_y += m_velocityY*deltaTime;
	
	if (m_velocityX != 0 && m_velocityY != 0)
	{
		en_pSprite->SetFrameSpeed(0.1);
	}
	else
	{
		en_pSprite->SetFrameSpeed(0.0000005);
	}

	if (en_enemyType == ROBORAT){
		roboratProcess();
	}
	else if (en_enemyType == ROBOSCORPIONDOG){
		roboscorpiondogProcess();
	}
	else if (en_enemyType == TIGERS){
		tigerProcess();
	}
	else if (en_enemyType == GRUNT){
		gruntProcess();
	}
	else if (en_enemyType == SCRAPSHOOTER){
		scrapshooterProcess();
	}
	else if (en_enemyType == BOSS){
		bossProcess();
	}
	en_pSprite->Process(deltaTime);
	en_currentRoomX = (m_x / 1280);
	en_currentRoomY = (m_y / 720);
}



int
Enemy::getHealth(){
	return en_health;
}

void
Enemy::setHealth(int health){
	en_health = health;
}

int
Enemy::getAttackSpeed(){
	return en_attackSpeed;
}

void
Enemy::getAttackSpeed(int attackSpeed){
	en_attackSpeed = attackSpeed;
}

int
Enemy::getAttackDamage(){
	return en_attackDamage;
}

void
Enemy::getAttackDamage(int attackDamage){
	en_attackDamage = attackDamage;
}

int
Enemy::getMovementSpeed(){
	return en_movementSpeed;
}

void
Enemy::setMovementSpeed(int movementSpeed){
	en_movementSpeed = movementSpeed;
}

int
Enemy::fireTimeRemaining(){
	return en_remainingDurationFire;
}

int
Enemy::poisonedTimeRemaining(){
	return en_remainingDurationPoisoned;
}

int
Enemy::electrocutedTimeRemaining(){
	return en_remainingDurationElectrocuted;
}

int
Enemy::repairingTimeRemaining(){
	return en_remainingDurationRepairing;
}

void
Enemy::setOnFire(int duration){
	en_remainingDurationFire = duration;

}

void
Enemy::setPoisoned(int duration){
	en_remainingDurationPoisoned = duration;
}

void
Enemy::setElectrocuted(int duration){
	en_remainingDurationElectrocuted = duration;
}

void
Enemy::setRepairing(int duration){
	en_remainingDurationRepairing = duration;
}

void
Enemy::setInitialRoboratStats(){
	en_attackDamage = 1;
	en_attackSpeed = 1;
	en_health = 100;
	en_movementSpeed = 1;
}

void
Enemy::setInitialRoboscorpiondogStats(){
	en_attackDamage = 1;
	en_attackSpeed = 1;
	en_health = 100;
	en_movementSpeed = 1;
}
void
Enemy::setInitialTigerStats(){
	en_attackDamage = 1;
	en_attackSpeed = 1;
	en_health = 100;
	en_movementSpeed = 1;
}
void
Enemy::setInitialGruntStats(){
	en_attackDamage = 1;
	en_attackSpeed = 1;
	en_health = 100;
	en_movementSpeed = 1;
}
void
Enemy::setInitialScrapshooterStats(){
	en_attackDamage = 1;
	en_attackSpeed = 1;
	en_health = 100;
	en_movementSpeed = 1;
}
void
Enemy::setInitialBossStats(){
	en_attackDamage = 1;
	en_attackSpeed = 1;
	en_health = 100;
	en_movementSpeed = 1;
}

void
Enemy::setInitialStats(){
	if (en_enemyType == ROBORAT){
		setInitialRoboratStats();
	}
	else if (en_enemyType == ROBOSCORPIONDOG){
		setInitialRoboscorpiondogStats();
	}
	else if (en_enemyType == TIGERS){
		setInitialTigerStats();
	}
	else if (en_enemyType == GRUNT){
		setInitialGruntStats();
	}
	else if (en_enemyType == SCRAPSHOOTER){
		setInitialScrapshooterStats();
	}
	else if (en_enemyType == BOSS){
		setInitialBossStats();
	}
}

void
Enemy::roboratProcess(){
	if (en_enemyState == PASSIVE){
		
	}
	else if (en_enemyState == AGRO){

	}
	else if (en_enemyState == HIDING){

	}
}
void
Enemy::roboscorpiondogProcess(){
	if (en_enemyState == PASSIVE){

	}
	else if (en_enemyState == AGRO){

	}
	else if (en_enemyState == HIDING){

	}
}
void
Enemy::tigerProcess(){
	if (en_enemyState == PASSIVE){

	}
	else if (en_enemyState == AGRO){

	}
	else if (en_enemyState == HIDING){

	}
}
void
Enemy::gruntProcess(){
	if (en_enemyState == PASSIVE){

	}
	else if (en_enemyState == AGRO){

	}
	else if (en_enemyState == HIDING){

	}
}
void
Enemy::scrapshooterProcess(){
	if (en_enemyState == PASSIVE){

	}
	else if (en_enemyState == AGRO){

	}
	else if (en_enemyState == HIDING){

	}
}
void
Enemy::bossProcess(){
	if (en_enemyState == PASSIVE){
		if (m_x - (1280*4) < 100){
			m_velocityX = 100;
		}
		if (m_x - (1280 * 4) > 900){
			m_velocityX = -100;
		}
		if (toShoot > 14){
			//shoot
			toShoot = 0;
		}
		else {
			toShoot++;
		}
	}
	else if (en_enemyState == AGRO){

	}
	else if (en_enemyState == HIDING){

	}
}