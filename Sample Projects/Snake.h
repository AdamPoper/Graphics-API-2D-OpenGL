#pragma once

#include <AP2DGL/Renderer.h>
#include "Utils.h"

class SnakeNode
{
public:
	SnakeNode();
	SnakeNode(ap::Vec2f pos);
	ap::Quad& Get();
public:
	SnakeNode* next;
	SnakeNode* prev;
private:
	ap::Quad m_node;
public:
	static const ap::Vec2f s_size;
};

class Snake
{
public:
	Snake();
	~Snake();
	void Append();
	void Draw(ap::Renderer& renderer);
	void Move(ap::Vec2f moveAmount, ap::TimeStep& ts);
	bool EatFood(ap::Vec2f foodPos);
	bool CheckCollision();
	void clear();
private:
	SnakeNode* m_head;
	uint32_t m_size;    // number of quads the snake has
};
