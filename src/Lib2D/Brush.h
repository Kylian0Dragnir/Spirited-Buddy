#pragma once

class Vector2f;
class Window;

class Brush
{
public:
	static void DrawPoint(Window* _window, int _x, int _y);
	static void DrawRect(Window* _window, int _x, int _y, int _width, int _height);
	static void DrawCircle(Window* _window, Vector2f center, int radius, int precision);
};

