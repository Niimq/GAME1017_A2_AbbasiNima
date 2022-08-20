#pragma once
#ifndef _BOUND_H_
#define _BOUND_H_

#include "SDL.h"

class Bound
{
public: // Define some virtual functions of all bounds so no casting is required.
	virtual void Update(SDL_FPoint p) = 0;
	virtual const SDL_FPoint& GetCenter() = 0;
	virtual const double& GetRadius() = 0;
	virtual const SDL_FRect& GetRect() = 0;
};

class CircleBound : public Bound
{
public:
	CircleBound(SDL_FPoint p, double r);
	void Update(SDL_FPoint p);
	const SDL_FPoint& GetCenter() { return m_center; }
	const double& GetRadius() { return m_radius; }
private:
	SDL_FPoint m_center;
	double m_radius;
};

class RectBound : public Bound
{
public:
	RectBound(SDL_FRect r);
	void Update(SDL_FPoint p);
	const SDL_FRect& GetRect() { return m_rect; }
private:
	SDL_FRect m_rect;
};

#endif 
