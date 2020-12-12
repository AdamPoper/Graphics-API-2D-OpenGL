#pragma once

#include <AP2DGL/Renderer.h>
#include <random>

class Ball
{
public:
	float x, y;
public:
	Ball();
	void Draw(ap::Renderer& renderer);
	void Init(const ap::Circle& c);
	void OnUpdate(float ts);
	void calculateTrajectory(float degrees);
	void restart();
private:
	void randomizeTrajectory();
private:
	ap::Circle m_circle;
	ap::Vec2f m_trajectoryVector;
};