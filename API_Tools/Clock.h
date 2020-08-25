#pragma once
#include <chrono>
namespace ap {

	class Clock
	{
	public:
		Clock();
		void Restart();
		float GetElapsedTimeAsMilliseconds();  // returns as milliseconds
		float GetElapsedTimeAsSeconds();  // returns as Seconds
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startPoint;
		
	};
}
