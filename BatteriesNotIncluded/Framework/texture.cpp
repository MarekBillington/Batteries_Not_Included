// 717310 C++ SDL Framework

// This include:
#include "texture.h"

// Local includes:
#include "logmanager.h"

// Library include:
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cassert>

Texture::Texture()
: m_pTexture(0)
, m_height(0)
, m_width(0)
{
	m_flip = SDL_FLIP_NONE;
	TTF_Init();
}

Texture::~Texture()
{
	SDL_DestroyTexture(m_pTexture);
	m_pTexture = 0;
}

bool 
Texture::Initialise(const char* pcFilename, SDL_Renderer* pRenderer)
{
	m_pRenderer = pRenderer;

	SDL_Surface* pSurface = IMG_Load(pcFilename);

	if (pSurface == 0)
	{
		LogManager::GetInstance().Log("Image File Failed to Load!");
		return (false);
	}
	else
	{
		m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);

		if (m_pTexture == 0)
		{
			LogManager::GetInstance().Log("Texture Failed to Create!");
			return (false);
		}

		SDL_FreeSurface(pSurface);
	}

	SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND);

	SDL_QueryTexture(m_pTexture, 0, 0, &m_width, &m_height);

	return (m_pTexture != 0);
}

int 
Texture::GetWidth() const
{
	assert(m_width); 
	return (m_width);
}

int 
Texture::GetHeight() const
{
	assert(m_height);
	return (m_height);
}

SDL_Texture* 
Texture::GetTexture()
{
	return (m_pTexture);
}


bool 
Texture::loadText(SDL_Renderer* pRenderer, std::string textureText, SDL_Color textColor, std::string textFont, int textSize)
{
	m_pRenderer = pRenderer;

	TTF_Font* gFont = TTF_OpenFont(textFont.c_str(), textSize);

	//Get rid of preexisting texture
	//free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);

	if (textSurface == 0)
	{
		LogManager::GetInstance().Log("Image File Failed to Load!");
		return (false);
	}
	else
	{
		m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, textSurface);

		if (m_pTexture == 0)
		{
			LogManager::GetInstance().Log("Texture Failed to Create!");
			return (false);
		}

		SDL_FreeSurface(textSurface);
	}

	//assert(m_width);
	//m_width = textSurface->w;
	//assert(m_height);
	//m_height = textSurface->h;

	SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND);

	SDL_QueryTexture(m_pTexture, 0, 0, &m_width, &m_height);

	return (m_pTexture != 0);
}
