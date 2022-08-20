#include "Primitives.h"
#include "Engine.h"
#include "FontManager.h"

void Image::Render()
{
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), TEMA::GetTexture(m_key), &m_src, &m_dst);
}

void Line::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderDrawLineF(Engine::Instance().GetRenderer(), m_start.x, m_start.y, m_end.x, m_end.y);
}

void Rectangle::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), m_color.r, m_color.g, m_color.b, m_color.a);
	if (m_fill)
		SDL_RenderFillRectF(Engine::Instance().GetRenderer(), &m_dst);
	else
		SDL_RenderDrawRectF(Engine::Instance().GetRenderer(), &m_dst);
}

Label::Label(std::string key, const float x, const float y, const char* str,
	const SDL_Color col) :m_textColor(col)
{
	m_font = FontManager::GetFont(key);
	SetPos(x, y);
	SetText(str);
}

Label::~Label()
{
	SDL_DestroyTexture(m_pTexture);
}

void Label::Render()
{
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), m_pTexture, NULL, &m_dst);
}

void Label::SetText(const char* str)
{
	strcpy_s(m_string, 256, str);
	SDL_Surface* fontSurf = TTF_RenderText_Blended(m_font, m_string, m_textColor);
	SDL_DestroyTexture(m_pTexture);
	m_pTexture = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), fontSurf);
	m_dst = { m_dst.x, m_dst.y, (float)fontSurf->w, (float)fontSurf->h };
	SDL_FreeSurface(fontSurf);
}

void Label::SetPos(const float x, const float y)
{
	m_dst = { x, y, (float)m_dst.w, (float)m_dst.h };
}

void Label::SetColor(const SDL_Color& col)
{
	m_textColor = col;
	SetText(m_string);
}

void Label::UseFont(std::string key)
{
	m_font = FontManager::GetFont(key);
	SetText(m_string);
}
