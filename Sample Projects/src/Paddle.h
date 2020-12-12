#pragma once

#include <AP2DGL/Renderer.h>
#include "Util.h"

class Paddle
{
public:
	float x, y;  // position variables for easy access
public:
	Paddle();
	void Init(const ap::Quad& quadTemplate);
	void Draw(ap::Renderer& renderer);
	void HandleInput(uint32_t keyCode1, uint32_t keyCode2, float ts);
	void OnUpdate();
public:
	static float s_PaddleHeight;
private:
	ap::Quad m_quad;
	static float s_paddle_speed;
};