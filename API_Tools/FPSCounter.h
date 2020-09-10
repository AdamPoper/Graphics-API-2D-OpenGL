#pragma once
#include <GLFW/glfw3.h>
namespace ap {

	class FPScounter
	{
	public:
		FPScounter();			
		void OnUpdate();		
		double DrawFPS();
	private:
		double m_lastTime, m_fps;
		unsigned int m_numFrames;	
	};
}