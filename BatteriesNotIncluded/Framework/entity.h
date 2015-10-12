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
	bool IsDead() const;

	bool IsCollidingWith(Entity& e);

	float GetPositionX();
	float GetPositionY();

	float GetHorizontalVelocity();
	void SetHorizontalVelocity(float x); 

	float GetVerticalVelocity();
	void SetVerticalVelocity(float y);

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

	float m_velocityX;
	float m_velocityY;

	bool m_dead;

private:

};

#endif //__ENTITY_H__
