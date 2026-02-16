#pragma once

class Vector2f;
class Window;

class Brush
{
	Window* m_window;

public:
	Brush(Window* _window);

	void DrawPoint(int _x, int _y);
	void DrawRect(int _x, int _y, int _width, int _height);
	void DrawCircle(Vector2f center, int radius, int precision);
};

