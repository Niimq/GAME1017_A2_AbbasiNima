#include "Bound.h"

CircleBound::CircleBound(SDL_FPoint p, double r) :m_center(p), m_radius(r) {}

void CircleBound::Update(SDL_FPoint p)
{
	m_center = { p.x, p.y };
}

RectBound::RectBound(SDL_FRect r) : m_rect(r) {}

void RectBound::Update(SDL_FPoint p)
{
	m_rect = { p.x, p.y, m_rect.w, m_rect.h };
}
