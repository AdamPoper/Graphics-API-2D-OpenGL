#pragma once

#include <AP2DGL/Renderer.h>
#include <AP2DGL/API_Tools/Clock.h>

#include <memory>

#include "Util.h"
#include "Paddle.h"
#include "Ball.h"

namespace Application
{
	class Game
	{
	public:
		static void InitGame();
		static void RunGame();
	private:
		static Game s_instance;
	private:
		Game();
		void Run();
		void Init();
		void CollisionDetection(float& time);
	private:
		std::unique_ptr<ap::Renderer> m_renderer;
		std::unique_ptr<ap::Window> m_window;
		Paddle m_leftPaddle;
		Paddle m_rightPaddle;
		Ball m_ball;
		ap::TimeStep m_time;
		bool m_started = false;
	};
}