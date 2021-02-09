#pragma once

#include <AP2DGL/Renderer.h>
#include "Snake.h"
#include "Utils.h"
#include <random>

class Game
{
public:
	static Game& Get();
	static void InitGame();
	static void RunGame();
private:
	static Game s_instance;
private:
	Game();
	~Game();
	void Run();
	void Init();
	void InputHandle(ap::TimeStep& ts);
	void SpawnFood();
	void EatFoodActions();
private:
	Snake m_snake;
	ap::Window* m_window;
	ap::Renderer* m_renderer;
	ap::Clock m_gameClock;
	ap::Quad m_food;
	DIRECTIONS m_currentDirection;
};
