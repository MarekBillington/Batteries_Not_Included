// 717310 C++ SDL Framework
#ifndef __BACKBUFFER_H__
#define __BACKBUFFER_H__

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

// Forward Declarations:
class TextureManager;
class Sprite;
class AnimatedSprite;
struct SDL_Window;
struct SDL_Renderer;

class BackBuffer
{
	//Member Methods:
public:
	BackBuffer();
	~BackBuffer();

	bool Initialise(int width, int height);

	void Clear();
	void Present();

	void SetClearColour(unsigned char r, unsigned char g, unsigned char b);

	void SetDrawColour(unsigned char r, unsigned char g, unsigned char b);
	void SetDrawColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	void DrawSprite(Sprite& sprite);
	void DrawAnimatedSprite(AnimatedSprite& sprite);
	void DrawRectangle(int x1, int y1, int x2, int y2);
	void DrawLine(int x1, int y1, int x2, int y2);

	Sprite* CreateSprite(const char* pcFilename);
	Sprite* CreateText(std::string textureText, SDL_Color textColor, std::string textFont, int textSize);
	AnimatedSprite* CreateAnimatedSprite(const char* pcFilename);


	//tom
	void SetCameraX(float px);
	void SetCameraY(float py);
	float GetCameraX();
	float GetCameraY();

	//James
	void DrawRectangleOutline(int x1, int y1, int x2, int y2);
	void DrawSpriteHUD(Sprite& sprite);
	void SetSpriteAlpha(Sprite* t, unsigned char b);

	
protected:
	void LogSDLError();

private:
	BackBuffer(const BackBuffer& backBuffer);
	BackBuffer& operator=(const BackBuffer& backBuffer);

	//Member Data:
public:

protected:
	TextureManager* m_pTextureManager;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	int m_width;
	int m_height;

	//tom
	float m_bCameraX;
	float m_bCameraY;
	//

	unsigned char m_clearRed;
	unsigned char m_clearGreen;
	unsigned char m_clearBlue;
	
private:

};

#endif // __BACKBUFFER_H__
