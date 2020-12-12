#include "Game.h"

namespace Application
{
	Game Game::s_instance;

	Game::Game()
	{
	}
	void Game::Run()
	{
		float collideTime = 0.0f;
		while (m_window->isOpen())
		{
			if (ap::Window::isKeyPressed(ap::KEY_SPACE))
				m_started = true;
			float ts = m_time.GetElapsedTimeAsMilliseconds();
			collideTime += ts;
			m_time.Restart();
			if (m_started)
			{
				m_renderer->ClearRenderBuffer();
				m_leftPaddle.HandleInput(ap::KEY_W, ap::KEY_S, ts);
				m_rightPaddle.HandleInput(ap::KEY_UP, ap::KEY_DOWN, ts);
				m_leftPaddle.OnUpdate();
				m_rightPaddle.OnUpdate();
				m_ball.OnUpdate(ts);
				CollisionDetection(collideTime);
			}

			m_ball.Draw(*m_renderer);
			m_leftPaddle.Draw(*m_renderer);
			m_rightPaddle.Draw(*m_renderer);
			m_window->onUpdate();
		}
	}

	void Game::Init()
	{
		m_window = std::make_unique<ap::Window>(WIDTH, HEIGHT, "Pong");
		m_renderer = std::make_unique<ap::Renderer>(m_window.get());
		m_leftPaddle.Init(ap::Quad(ap::Vec2f(30.0f, HEIGHT / 2.0f), ap::Vec2f(20.0f, Paddle::s_PaddleHeight), ap::Color::White));
		m_rightPaddle.Init(ap::Quad(ap::Vec2f(WIDTH - 30.0f, HEIGHT / 2.0f), ap::Vec2f(20.0f, Paddle::s_PaddleHeight), ap::Color::White));
		m_ball.Init(ap::Circle(ap::Vec2f(WIDTH / 2.0f, HEIGHT / 2.0f), 10.0f, ap::Color::White));
	}

	void Game::CollisionDetection(float& ts)
	{
		float halfHeight = Paddle::s_PaddleHeight / 2.0f;
		if (ts > 100.0f)
		{
			// left paddle
			if (m_ball.x - 20.0f <= m_leftPaddle.x && (m_ball.y >= m_leftPaddle.y - halfHeight && m_ball.y <= m_leftPaddle.y + halfHeight))
			{
				if (m_ball.y >= m_leftPaddle.y - halfHeight && m_ball.y <= m_leftPaddle.y - 20.0f)
					m_ball.calculateTrajectory(-45.0f);
				else if (m_ball.y >= m_leftPaddle.y - 20.0f && m_ball.y <= m_leftPaddle.y)
					m_ball.calculateTrajectory(-15.0f);
				else if (m_ball.y <= m_leftPaddle.y + 20.0f && m_ball.y >= m_leftPaddle.y)
					m_ball.calculateTrajectory(15.0f);
				else if (m_ball.y <= m_leftPaddle.y + halfHeight && m_ball.y >= m_leftPaddle.y + 20.0f)
					m_ball.calculateTrajectory(45.0f);

			}
			// right paddle
			if (m_rightPaddle.x <= m_ball.x + 20.0f && (m_ball.y >= m_rightPaddle.y - halfHeight && m_ball.y <= m_rightPaddle.y + halfHeight))
			{
				if (m_ball.y >= m_rightPaddle.y - halfHeight && m_ball.y <= m_rightPaddle.y - 20.0f)
					m_ball.calculateTrajectory(135.0f);
				else if (m_ball.y >= m_rightPaddle.y - 20.0f && m_ball.y <= m_rightPaddle.y)
					m_ball.calculateTrajectory(165.0f);
				else if (m_ball.y <= m_rightPaddle.y + 20.0f && m_ball.y >= m_rightPaddle.y)
					m_ball.calculateTrajectory(195.0f);
				else if (m_ball.y <= m_rightPaddle.y + halfHeight && m_ball.y >= m_rightPaddle.y + 20.0f)
					m_ball.calculateTrajectory(225.0f);
			}
			// top
			if (m_ball.y - 10.0f <= 0.0f)
				m_ball.calculateTrajectory(1.0f);
			// bottom
			if (m_ball.y + 10.0f >= HEIGHT)
				m_ball.calculateTrajectory(0.0f);
			else if(m_ball.x < 0.0f || m_ball.x >= WIDTH)
				m_ball.restart();

			ts = 0.0f;
		}
	}

	void Game::RunGame()
	{
		s_instance.Run();
	}
	void Game::InitGame()
	{
		s_instance.Init();
	}
}
