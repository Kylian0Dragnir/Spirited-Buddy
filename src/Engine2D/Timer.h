#pragma once
#include <chrono>
#include <iostream>

class Timer
{
private:

	std::chrono::steady_clock::time_point m_startTime;
	bool m_started;

public:

	Timer();

	void StartTime();
	float Restart();
	void StopTime();

	float GetTime();

	bool IsStarted();
};