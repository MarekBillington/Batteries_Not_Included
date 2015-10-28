#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

#include "sprite.h"

#include <vector>

class BackBuffer;
class Texture;

class AnimatedSprite : public Sprite
{
	// Methods:
public:
	AnimatedSprite();
	~AnimatedSprite();

	bool Initialise(Texture& texture);
	void AddFrame(int x);
	void setLocation(int y);

	int getLocation();

	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);

	void SetFrameSpeed(float f);
	void SetFrameWidth(int w);

	int GetFrame();
	int GetWidth();

	void Pause();
	bool IsPaused();

	bool IsAnimating();
	void StartAnimating();

	bool IsLooping();
	void SetLooping(bool b);

protected:

private:

	// Fields:
public:

protected:
	// Ex007.1: Add a field, the container for frame coordinates.
	std::vector<int> frameCoordinates;
	int currentFrameSelection;

	float m_frameSpeed;
	int m_frameWidth;

	float m_timeElapsed;
	int m_currentFrame;

	bool m_paused;
	bool m_loop;
	bool m_animating;

private:

};

#endif // __ANIMATEDSPRITE_H__