// 717310 C++ SDL Framework
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

// Library includes:
#include <SDL.h>
#include <SDL_ttf.h>
#include "string"

class Texture
{
	//Member Methods:
public:
	Texture();
	~Texture();

	bool Initialise(const char* pcFilename, SDL_Renderer* pRenderer);

	bool loadText(SDL_Renderer* pRenderer, std::string textureText, SDL_Color textColor, std::string textFont, int textSize);

	int GetWidth() const;
	int GetHeight() const;

	SDL_Texture* GetTexture();

protected:

private:
	Texture(const Texture& texture);
	Texture& operator=(const Texture& texture);

	//Member Data:
public:

protected:
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;

	int m_width;
	int m_height;

	SDL_RendererFlip m_flip;

private:

};

#endif // __TEXTURE_H__
