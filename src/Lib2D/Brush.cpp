#include "Brush.h"
#include "SDL.h"
#include "Window.h"
#include "Vector2f.h"

#define M_PI 3.14159265358979323846

void Brush::DrawPoint(Window* _window, int _x, int _y)
{
	SDL_RenderDrawPoint(_window->m_renderer, _x, _y);
}

void Brush::DrawRect(Window* _window, int _x, int _y, int _width, int _height)
{
	SDL_SetRenderDrawColor(_window->m_renderer, 0, 255, 0, 255);

	SDL_Rect rect{ _x, _y, _width, _height };
	SDL_RenderDrawRect(_window->m_renderer, &rect);
}

void Brush::DrawCircle(Window* _window, Vector2f center, int radius, int precision)
{
	float step = (2 * M_PI) / precision;

	int x1 = center.GetX() + radius * cos(0);
	int y1 = center.GetY() + radius * sin(0);

	for (int i = 0; i < precision; i++)
	{
		float nextAngle = (i + 1) * step;

		int x2 = center.GetX() + radius * cos(nextAngle);
		int y2 = center.GetY() + radius * sin(nextAngle);

		SDL_RenderDrawLine(_window->m_renderer, x1, y1, x2, y2);

		x1 = x2;
		y1 = y2;
	}
}
