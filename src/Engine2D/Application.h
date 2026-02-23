#pragma once
#include <string>

class Window;

class Application
{
	Window* m_window;
	int m_FPS;

	bool m_isMusicMute;
	bool m_isSFXMute;

	Application();

public:
	~Application();
	static Application& Get();
	void InitApp(const std::string& _title, int _width, int _height, int _targetFPS = 60);
	void SetFPS(int _fps) { m_FPS = _fps; }
	void SetMusicMute(bool mute) { m_isMusicMute = mute; }
	void SetSFXMute(bool mute) { m_isSFXMute = mute; }
	bool GetMute() { return m_isMusicMute; }
	void LoopApp();
	void ShutDownApp();
};

