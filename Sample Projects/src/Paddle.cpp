#include "Paddle.h"

float Paddle::s_paddle_speed = 0.75f;
float Paddle::s_PaddleHeight = 100.0f;

Paddle::Paddle()
{
	m_quad.setSize(ap::Vec2f(30.0f, 100.0f));
	m_quad.setColor(ap::Color::White);
}
void Paddle::Init(const ap::Quad& quad)
{
	m_quad.setColor(quad.getColor());
	m_quad.setPosition(quad.getPosition());
	m_quad.setSize(quad.getSize());
	OnUpdate();
}
void Paddle::Draw(ap::Renderer& renderer)
{
	renderer.Draw(&m_quad);
}
void Paddle::HandleInput(uint32_t keyCode1, uint32_t keyCode2, float ts)
{
	// keycode1 is for up operations, keycode 2 is for down operations
	if (ap::Window::isKeyPressed(keyCode1) && m_quad.getPosition().y >= 0.0f)
	{
		m_quad.move(ap::Vec2f(0.0f, -s_paddle_speed * ts));
		if (m_quad.getPosition().y <= 0.0f)
			m_quad.move(ap::Vec2f(0.0f, s_paddle_speed * ts));
	}
	if (ap::Window::isKeyPressed(keyCode2))
	{
		m_quad.move(ap::Vec2f(0.0f, s_paddle_speed * ts));
		if (m_quad.getPosition().y >= HEIGHT)
			m_quad.move(ap::Vec2f(0.0f, -s_paddle_speed * ts));
	}
}
void Paddle::OnUpdate()
{
	this->x = m_quad.getPosition().x;
	this->y = m_quad.getPosition().y;
}