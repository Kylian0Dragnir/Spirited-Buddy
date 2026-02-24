#pragma once
#include <string>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
class Drawable;

class Window
{
private:

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	const int VIRTUAL_WIDTH = 1920;
	const int VIRTUAL_HEIGHT = 1080;

	SDL_Texture* m_renderTarget = nullptr;

	bool m_isOpen;
	int m_width;
	int m_height;

public:
	Window();
	~Window();

	void Create(const std::string& _title, int _w, int _h);
	bool GetIsOpen();
	void SetIsOpen(bool _isOpen);
	void ClearWindow();
	void Draw(Drawable* p);
	void Display();

	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }

	int GetVirtualWidth() { return VIRTUAL_WIDTH; }
	int GetVirtualHeight() { return VIRTUAL_HEIGHT; }

	friend class Sprite;
	friend class AssetManager;
	friend class Text;
	friend class Brush;
};

