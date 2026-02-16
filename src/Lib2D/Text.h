#pragma once
#include <string>
#include "Window.h"
#include "Transformable.h"
#include "Drawable.h"

class Texture;

struct TTF_Font;

class Text : public Transformable, Drawable
{
private:
	Texture* m_texture;
	SDL_Surface* m_surface;
	SDL_Color m_color;
	TTF_Font* m_font;

public:

	Text();
	void Init(std::string _fontPath, int _size); 
	void SetText(std::string _text);
	void SetDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void Draw(Window* _window) override;
	~Text();

};

