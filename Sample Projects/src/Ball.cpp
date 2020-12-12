#include "Ball.h"
#include "Util.h"

Ball::Ball()
	: x(0.0f), y(0.0f)
{
}
void Ball::Draw(ap::Renderer& renderer)
{
	renderer.Draw(&m_circle);
}
void Ball::Init(const ap::Circle& c)
{
	m_circle.setColor(c.getColor());
	m_circle.setRadius(c.GetRadius());
	m_circle.setPosition(c.getPosition());
	randomizeTrajectory();
}
void Ball::randomizeTrajectory()
{
	std::srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	float degrees = (float)(std::rand() % 65);
	m_trajectoryVector.x = glm::cos(glm::radians(degrees));
	m_trajectoryVector.y = glm::sin(glm::radians(degrees));
	// randomize a flip in the directions so the ball doesn't always start out in the bottom half
	int x = std::rand() % 2;
	int y = std::rand() % 2;
	m_trajectoryVector.x = x == 1 ? m_trajectoryVector.x * -1.0f : m_trajectoryVector.x;
	m_trajectoryVector.y = y == 1 ? m_trajectoryVector.y * -1.0f : m_trajectoryVector.y;

}
void Ball::OnUpdate(float ts)
{
	float speed = 0.55f;
	float x = m_trajectoryVector.x * ts * speed;
	float y = m_trajectoryVector.y * ts * speed;
	m_circle.move({ x, y });
	this->x = m_circle.getPosition().x;
	this->y = m_circle.getPosition().y;
}

void Ball::calculateTrajectory(float degrees)
{
	// 1.0f for the top or 0.0f for the bottom
	if (degrees == 1.0f || degrees == 0.0f)
		m_trajectoryVector.y *= -1.0f;
	else
	{
		m_trajectoryVector.x = glm::cos(glm::radians(degrees));
		m_trajectoryVector.y = glm::sin(glm::radians(degrees));
	}
}

void Ball::restart()
{
	m_circle.setPosition(ap::Vec2f(WIDTH / 2.0f, HEIGHT / 2.0f));
	randomizeTrajectory();
}