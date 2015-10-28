// This includes:
#include "animatedsprite.h"

// Local includes:
#include "texture.h"
#include "backbuffer.h"

AnimatedSprite::AnimatedSprite()
: m_frameSpeed(0.0f)
, m_frameWidth(0)
, m_timeElapsed(0.0f)
, m_currentFrame(0)
, m_paused(false)
, m_loop(false)
, m_animating(false)
{

}

AnimatedSprite::~AnimatedSprite()
{

}

bool
AnimatedSprite::Initialise(Texture& texture)
{
	m_frameWidth = 0;
	m_frameSpeed = 0;

	m_loop = false;
	m_paused = false;
	m_animating = true;

	Sprite::Initialise(texture);

	StartAnimating();

	return (true);
}

void
AnimatedSprite::AddFrame(int x)
{
	// Ex007.1: Add the x coordinate to the frame coordinate container.
	frameCoordinates.push_back(x);
}

void
AnimatedSprite::Process(float deltaTime)
{

	// Ex007.1: If not paused...
	// Ex007.1: Count the time elapsed.
	if (!IsPaused())
	{
		m_timeElapsed += deltaTime;
	}

	// Ex007.1: If the time elapsed is greater than the frame speed.

	// Ex007.1: Move to the next frame.
	// Ex007.1: Reset the time elapsed counter.

	if (m_timeElapsed > m_frameSpeed)
	{
		m_currentFrame++;
		m_timeElapsed = 0;
	}


	// Ex007.1: Stop the animation if it is not looping...
	if (m_currentFrame == frameCoordinates.size() && !IsLooping())
	{
		m_paused = true;
	}

	// Ex007.1: If the current frame is greater than the number 
	//          of frame in this animation...
	// Ex007.1: Reset to the first frame.

	if (m_currentFrame > frameCoordinates.size())
	{
		m_currentFrame = 0;
	}



}

void
AnimatedSprite::Draw(BackBuffer& backbuffer)
{
	// Ex007.1: Draw the particular frame into the backbuffer.

	//          What is the current frame's x coordinate?
	//          What is the frame width?


	this->m_width = m_frameWidth;

	backbuffer.DrawAnimatedSprite(*this);
}

int
AnimatedSprite::GetFrame()
{
	return (m_currentFrame);
}

void
AnimatedSprite::SetFrameSpeed(float f)
{
	m_frameSpeed = f;
}

void
AnimatedSprite::SetFrameWidth(int w)
{
	m_frameWidth = w;
}

void
AnimatedSprite::Pause()
{
	m_paused = !m_paused;
}

bool
AnimatedSprite::IsPaused()
{
	return (m_paused);
}

bool
AnimatedSprite::IsAnimating()
{
	return (m_animating);
}

void
AnimatedSprite::StartAnimating()
{
	m_animating = true;

	m_timeElapsed = 0;
	m_currentFrame = 0;
}

bool
AnimatedSprite::IsLooping()
{
	return (m_loop);
}

void
AnimatedSprite::SetLooping(bool b)
{
	m_loop = b;
}