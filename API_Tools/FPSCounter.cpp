#include "FPSCounter.h"
namespace ap {
	FPScounter::FPScounter()
		: m_fps(0)
	{
		m_numFrames = 0;
		m_lastTime = glfwGetTime();
	}
	void FPScounter::OnUpdate()
	{		
		double currentTime = glfwGetTime();
		m_numFrames++;
		if (currentTime - m_lastTime >= 1.0f)
		{
			m_fps = (double)m_numFrames / (currentTime - m_lastTime);
			m_numFrames = 0;
			m_lastTime += 1.0;
		}
	}
	double FPScounter::DrawFPS() { return m_fps; }	
}