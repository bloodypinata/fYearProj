#include "Sprite.h"
#include <string>
#include "main.h"

int frameCount = 0;

Sprite::Sprite()
{
	_spriteTexture = nullptr;
	_name = "";
	_xPos = 0;
	_yPos = 0;
	_sHeight = 0;
	_sWidth = 0;
	_spriteSheetOffset = 0;
	_animation = false;
	_mainCharacter = false;
}
Sprite::~Sprite()
{
	free();
}

//possibly depricated
//bool Sprite::loadFromFile(std::string path)
//{
//	bool success = false;
//	_animation = false;
//	//the texture that will become the sprite
//	SDL_Texture* tempTexture = NULL;
//
//	//load the file into memory
//	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//	if (loadedSurface != NULL)
//	{
//		//consider how to handle wanted transparancy
//		//SDL_SetColorKey()
//
//		//converting the surface to a texture
//		tempTexture = SDL_CreateTextureFromSurface(g_renderer, loadedSurface);
//		if (tempTexture != NULL)
//		{
//			_sHeight = loadedSurface->h;
//			_sWidth = loadedSurface->w;
//			success = true;
//		}
//	}
//	
//	_spriteTexture = tempTexture;
//	return success;
//}

bool Sprite::loadFromFile(std::string path, bool animate)
{
	bool success = false;
	_animation = animate;
	
	//the texture that will become the sprite
	SDL_Texture* tempTexture = nullptr;

	//load the file into memory
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface != nullptr)
	{
		//consider handling transperancy here
		//SDL_SetColorKey()

		//converting the surface to a texture
		tempTexture = SDL_CreateTextureFromSurface(g_renderer, loadedSurface);
		if (tempTexture != nullptr)
		{
			_sHeight = loadedSurface->h;
			_sWidth = loadedSurface->w;
			success = true;
		}
		if (animate)
		{
			_sWidth = _sWidth / WALKING_FRAMES;
			_sHeight = _sHeight / SPRITE_SHEET_COUNT;

			//Set sprite clips

			//idling
			_gSpriteClips[0].x = _sWidth * 0;
			_gSpriteClips[0].y = _sHeight * 0;
			_gSpriteClips[0].w = _sWidth;
			_gSpriteClips[0].h = _sHeight;

			_gSpriteClips[1].x = _sWidth * 1;
			_gSpriteClips[1].y = _sHeight * 0;
			_gSpriteClips[1].w = _sWidth;
			_gSpriteClips[1].h = _sHeight;

			_gSpriteClips[2].x = _sWidth * 2;
			_gSpriteClips[2].y = _sHeight * 0;
			_gSpriteClips[2].w = _sWidth;
			_gSpriteClips[2].h = _sHeight;

			_gSpriteClips[3].x = _sWidth * 3;
			_gSpriteClips[3].y = _sHeight * 0;
			_gSpriteClips[3].w = _sWidth;
			_gSpriteClips[3].h = _sHeight;

			//punching
			_gSpriteClips[0 + PUNCH].x = _sWidth * 0;
			_gSpriteClips[0 + PUNCH].y = _sHeight * 1;
			_gSpriteClips[0 + PUNCH].w = _sWidth;
			_gSpriteClips[0 + PUNCH].h = _sHeight;

			_gSpriteClips[1 + PUNCH].x = _sWidth * 1;
			_gSpriteClips[1 + PUNCH].y = _sHeight * 1;
			_gSpriteClips[1 + PUNCH].w = _sWidth;
			_gSpriteClips[1 + PUNCH].h = _sHeight;

			_gSpriteClips[2 + PUNCH].x = _sWidth * 2;
			_gSpriteClips[2 + PUNCH].y = _sHeight * 1;
			_gSpriteClips[2 + PUNCH].w = _sWidth;
			_gSpriteClips[2 + PUNCH].h = _sHeight;

			_gSpriteClips[3 + PUNCH].x = _sWidth * 3;
			_gSpriteClips[3 + PUNCH].y = _sHeight * 1;
			_gSpriteClips[3 + PUNCH].w = _sWidth;
			_gSpriteClips[3 + PUNCH].h = _sHeight;

			//walking
			_gSpriteClips[0 + WALK].x = _sWidth * 0;
			_gSpriteClips[0 + WALK].y = _sHeight * 2;
			_gSpriteClips[0 + WALK].w = _sWidth;
			_gSpriteClips[0 + WALK].h = _sHeight;

			_gSpriteClips[1 + WALK].x = _sWidth * 1;
			_gSpriteClips[1 + WALK].y = _sHeight * 2;
			_gSpriteClips[1 + WALK].w = _sWidth;
			_gSpriteClips[1 + WALK].h = _sHeight;

			_gSpriteClips[2 + WALK].x = _sWidth * 2;
			_gSpriteClips[2 + WALK].y = _sHeight * 2;
			_gSpriteClips[2 + WALK].w = _sWidth;
			_gSpriteClips[2 + WALK].h = _sHeight;

			_gSpriteClips[3 + WALK].x = _sWidth * 3;
			_gSpriteClips[3 + WALK].y = _sHeight * 2;
			_gSpriteClips[3 + WALK].w = _sWidth;
			_gSpriteClips[3 + WALK].h = _sHeight;

			//jumping
			_gSpriteClips[0 + JUMP].x = _sWidth * 0;
			_gSpriteClips[0 + JUMP].y = _sHeight * 5;
			_gSpriteClips[0 + JUMP].w = _sWidth;
			_gSpriteClips[0 + JUMP].h = _sHeight;

			_gSpriteClips[1 + JUMP].x = _sWidth * 1;
			_gSpriteClips[1 + JUMP].y = _sHeight * 5;
			_gSpriteClips[1 + JUMP].w = _sWidth;
			_gSpriteClips[1 + JUMP].h = _sHeight;

			_gSpriteClips[2 + JUMP].x = _sWidth * 2;
			_gSpriteClips[2 + JUMP].y = _sHeight * 5;
			_gSpriteClips[2 + JUMP].w = _sWidth;
			_gSpriteClips[2 + JUMP].h = _sHeight;

			_gSpriteClips[3 + JUMP].x = _sWidth * 3;
			_gSpriteClips[3 + JUMP].y = _sHeight * 5;
			_gSpriteClips[3 + JUMP].w = _sWidth;
			_gSpriteClips[3 + JUMP].h = _sHeight;
		}
	}

	_spriteTexture = tempTexture;
	return success;
}

void Sprite::free()
{
	SDL_DestroyTexture(_spriteTexture);
	_sHeight = 0;
	_sWidth = 0;
}


void Sprite::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) const
{
	SDL_Rect renderQuad = { x, y, _sWidth, _sHeight };

	if (_mainCharacter)
	{
		renderQuad.w = _gSpriteClips[frameCount/WALKING_FRAMES].w;
		renderQuad.h = _gSpriteClips[frameCount/WALKING_FRAMES].h;
	}
	else if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	if (!_mainCharacter)
	{
		SDL_RenderCopyEx(g_renderer, _spriteTexture, clip, &renderQuad, angle, center, flip);
	}
	else
	{
		if (_flip)
		{
			SDL_RenderCopyEx(g_renderer, _spriteTexture, &_gSpriteClips[(frameCount / WALKING_FRAMES) + _spriteSheetOffset], &renderQuad, angle, center, _sFlip);
		}
		else
		{
			SDL_RenderCopyEx(g_renderer, _spriteTexture, &_gSpriteClips[(frameCount / WALKING_FRAMES) + _spriteSheetOffset], &renderQuad, angle, center, flip);
		}
		frameCount++;

		if (frameCount / WALKING_FRAMES >= WALKING_FRAMES)
		{
			frameCount = 0;
		}
	}
}

void Sprite::setXPos(int x)
{
	_xPos = x;
}

void Sprite::setYPos(int y)
{
	_yPos = y;
}

int Sprite::getHeight() const
{
	return _sHeight;
}

int Sprite::getWidth() const
{
	return _animation ? _sWidth / WALKING_FRAMES :_sWidth;
}

int Sprite::getXPos()
{
	return _xPos;
}

int Sprite::getYPos()
{
	return _yPos;
}

void Sprite::sFlip(bool flip)
{
	_flip = flip;
}

void Sprite::setName(std::string name)
{
	_name = name;
}

void Sprite::setSpriteSheetOffset(int offset)
{
	_spriteSheetOffset = offset;
}

void Sprite::isMainChar()
{
	_mainCharacter = true;
}

std::string Sprite::getName()
{
	return _name;
}

void Sprite::animate()
{
}
