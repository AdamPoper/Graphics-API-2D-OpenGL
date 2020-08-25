#include "Clock.h"

namespace ap {

	Clock::Clock()
	{
		m_startPoint = std::chrono::high_resolution_clock::now();
	}
	void Clock::Restart()
	{
		m_startPoint = std::chrono::high_resolution_clock::now();
	}
	float Clock::GetElapsedTimeAsMilliseconds()
	{
		auto endtime = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_startPoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::milliseconds>(endtime).time_since_epoch().count();
		auto duration = end - start;
		return duration;
	}
	float Clock::GetElapsedTimeAsSeconds()
	{
		auto endtime = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_startPoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::milliseconds>(endtime).time_since_epoch().count();
		auto duration = end - start;
		return duration * 0.001f;
	}
}
