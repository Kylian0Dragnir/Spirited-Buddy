#pragma once
#include <string>

struct SDL_Window;
struct SDL_Renderer;
class Drawable;

class Window
{
private:

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	bool m_isOpen;
	int m_width;
	int m_height;
	int m_x;
	int m_y;

public:
	Window();
	~Window();

	void Create(const std::string& _title, int _w, int _h, int _x, int _y);
	bool GetIsOpen();
	void SetIsOpen(bool _isOpen);
	void ClearWindow();
	void Draw(Drawable* p);
	void Display();
	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }

	friend class Sprite;
	friend class AssetManager;
	friend class Text;
	friend class Brush;
};

