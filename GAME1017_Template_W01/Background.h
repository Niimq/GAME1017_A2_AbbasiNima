#pragma once

#include "GameObject.h"
#include "SDL.h"

class Background : public SpriteObject
{
private:
	float m_scrollSpeed;
	float m_startX;
	float m_endX;

public:
	Background(const SDL_Rect& source, const SDL_FRect& destination, float scrollSpeed);
	void Update();
	void Render();
};
