#pragma once
#include <string>

class Window;

class Application
{
	Window* m_window;
	int m_FPS;

	bool m_isMute;

	Application();

public:
	~Application();
	static Application& Get();
	void InitApp(const std::string& _title, int _width, int _height, int _targetFPS = 60);
	void SetFPS(int _fps) { m_FPS = _fps; }
	void SetMute(bool mute) { m_isMute = mute; }
	bool GetMute() { return m_isMute; }
	void LoopApp();
	void ShutDownApp();
};

