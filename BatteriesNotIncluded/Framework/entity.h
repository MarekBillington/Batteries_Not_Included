// 717310 C++ SDL Framework
#ifndef __ENTITY_H__
#define __ENTITY_H__

// Forward Declarations:
class BackBuffer;
class Sprite;

class Entity
{
	//Member Methods:
public:
	Entity();
	~Entity();

	bool Initialise(Sprite* sprite);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void SetDead(bool dead);
	bool IsDead();

	bool IsCollidingWith(Entity& e);

	float GetPositionX();
	void  SetPositionX(float x);
	float GetPositionY();
	void  SetPositionY(float y);

	int getCurrentRoomX();	//- moved to entity
	int getCurrentRoomY();
	void setCurrentRoomX(int x);	//- moved to entity
	void setCurrentRoomY(int y);

	float GetHorizontalVelocity();
	void SetHorizontalVelocity(float x);

	float GetVerticalVelocity();
	void SetVerticalVelocity(float y);

	Sprite* getSprite();
	int getWidth();
	int getHeight();
	void setWidth(int w);
	void setHeight(int h);

	bool isPlayer();

	int getHealth();
	void setHealth(int health);
protected:

private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);

	//Member Data:
public:

protected:
	Sprite* m_pSprite;

	float m_x;
	float m_y;

	int en_currentRoomX;
	int en_currentRoomY;

	float m_velocityX;
	float m_velocityY;

	bool m_dead;
	int en_width;
	int en_height;

	int en_health;
private:

};

#endif //__ENTITY_H__
