#pragma once

class Window;

class Drawable
{
public:

	virtual void Draw(Window* _window) = 0;
};
