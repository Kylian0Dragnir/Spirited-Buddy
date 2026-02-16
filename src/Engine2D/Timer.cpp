#include "Timer.h"

Timer::Timer()
{
	m_started = false;
}

void Timer::StartTime()
{
	m_started = true;

	m_startTime = std::chrono::steady_clock::now();
}

float Timer::Restart()
{
	auto now = std::chrono::steady_clock::now();
	std::chrono::duration<float> diff = now - m_startTime;
	m_startTime = now;
	return diff.count();
}

void Timer::StopTime()
{
	m_started = false;
}

float Timer::GetTime()
{
	if (m_started == true)
	{
		const std::chrono::duration<float> diff = std::chrono::steady_clock::now() - m_startTime;
		return diff.count();
	}

	return 0;
}

bool Timer::IsStarted()
{
	return m_started;
}

