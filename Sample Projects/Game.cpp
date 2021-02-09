#include "Game.h"


Game Game::s_instance;

Game::Game()
{
}
Game::~Game()
{
	delete m_renderer;
	delete m_window;
}
void Game::InitGame()
{
	s_instance.Init();
}
void Game::RunGame()
{
	s_instance.Run();
}

void Game::InputHandle(ap::TimeStep& ts)
{
	if (ap::Window::isKeyPressed(ap::KEY_W))
		m_currentDirection = DIRECTIONS::up;

	if (ap::Window::isKeyPressed(ap::KEY_A))
		m_currentDirection = DIRECTIONS::left;
	
	if (ap::Window::isKeyPressed(ap::KEY_S))
		m_currentDirection = DIRECTIONS::down;	
	
	if (ap::Window::isKeyPressed(ap::KEY_D))
		m_currentDirection = DIRECTIONS::right;
	
	switch (m_currentDirection)
	{
		case DIRECTIONS::up:
			m_snake.Move(ap::Vec2f(0.0f, -SnakeNode::s_size.y), ts);
			break;
		case DIRECTIONS::left:
			m_snake.Move(ap::Vec2f(-SnakeNode::s_size.x, 0.0f), ts);
			break;
		case DIRECTIONS::down:
			m_snake.Move(ap::Vec2f(0.0f, SnakeNode::s_size.y), ts);
			break;
		case DIRECTIONS::right:
			m_snake.Move(ap::Vec2f(SnakeNode::s_size.x, 0.0f), ts);
			break;
	}
}

void Game::Run()
{
	while (m_window->isOpen())
	{
		float ts = m_gameClock.GetElapsedTimeAsMilliseconds();

		m_renderer->ClearRenderBuffer();

		InputHandle(m_gameClock);

		EatFoodActions();

		m_renderer->Draw(&m_food);

		m_snake.Draw(*m_renderer);

		m_window->onUpdate();
	}
}

void Game::SpawnFood()
{
	m_food.setPosition({ SnakeNode::s_size.x / 2.0f, SnakeNode::s_size.y / 2.0f });

	std::srand(time(nullptr));
	float x = (float)(std::rand() % (int)(WIDTH / SnakeNode::s_size.x));
	float y = (float)(std::rand() % (int)(WIDTH / SnakeNode::s_size.y));

	m_food.move(
		ap::Vec2f((x * SnakeNode::s_size.x),
			y * SnakeNode::s_size.y));
	m_food.setColor(ap::Color::Blue);
	m_food.setSize(SnakeNode::s_size);
}

void Game::EatFoodActions()
{
	if (m_snake.EatFood(m_food.getPosition()))
	{
		m_snake.Append();
		SpawnFood();
	}
}

void Game::Init()
{
	m_window = new ap::Window(WIDTH, HEIGHT, "Window");
	m_renderer = new ap::Renderer(m_window);
	SpawnFood();
}

Game& Game::Get()
{
	return s_instance;
}
