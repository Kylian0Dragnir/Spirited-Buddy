#pragma once
#include <string>

class Window;

class Application
{
	Window* m_window;
	int m_FPS;
	Application();

public:
	~Application();
	static Application& Get();
	void InitApp(const std::string& _title, int _width, int _height, int _targetFPS = 60);
	void SetFPS(int _fps) { m_FPS = _fps; }
	void LoopApp();
	void ShutDownApp();
};

