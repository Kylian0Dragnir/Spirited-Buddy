#include "Text.h"
#include <SDL_ttf.h>
#include "Texture.h"

Text::Text() : Transformable({ 0, 0 }) {

	m_font = nullptr;
	m_texture = nullptr;
	m_surface = nullptr;
	m_color = { 255, 255, 255, 255 };
}

void Text::Init(std::string _fontPath, int _size)
{
	m_font = TTF_OpenFont(_fontPath.c_str(), _size);
}

void Text::SetText(std::string _text)
{
	if (m_surface)
	{
		SDL_FreeSurface(m_surface);
	}

	if (m_texture)
	{
		delete m_texture;
		m_texture = nullptr;
	}

	TTF_SetFontStyle(m_font, TTF_STYLE_NORMAL);
	m_surface = TTF_RenderText_Blended_Wrapped(m_font, _text.c_str(), m_color, 1000);
}

void Text::SetDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	m_color = { r, g, b, a };
}

void Text::Draw(Window* _window)
{
	if (m_texture == nullptr)
	{
		m_texture = new Texture;
		SDL_Texture* texture = SDL_CreateTextureFromSurface(_window->m_renderer, m_surface);
		m_texture->SetDataPtr(texture);
	}

	int w, h;
	SDL_QueryTexture((SDL_Texture*)m_texture->GetDataPtr(), NULL, NULL, &w, &h);

	SDL_Rect dst(m_pos.GetX() - w * 0.5f, m_pos.GetY() - h * 0.5f, w, h);
	SDL_RenderCopy(_window->m_renderer, (SDL_Texture*)m_texture->GetDataPtr(), nullptr, &dst);
}

Text::~Text()
{
	if(m_font)
		TTF_CloseFont(m_font);
	if(m_texture)
		delete m_texture;
}
