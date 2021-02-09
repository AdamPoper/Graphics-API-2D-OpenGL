#include "Snake.h"

/// <summary>
///		Snake Implementations
/// </summary>

Snake::Snake()
{
	m_head = new SnakeNode(ap::Vec2f((WIDTH / 2.0f) + 20.0f, (HEIGHT / 2.0f) + 20.0f));
}
Snake::~Snake()
{
	clear();
}
void Snake::Append()
{
	if (m_head->next == nullptr)
	{
		m_head->next = new SnakeNode(m_head->Get().getPosition());
		m_head->next->prev = m_head;
		return;
	}
	
	SnakeNode* current = m_head;
	while (current->next != nullptr)
	{
		current = current->next;
	}
	current->next = new SnakeNode(current->Get().getPosition());
	current->next->prev = current;
	current->next->next = nullptr;
}

void Snake::Draw(ap::Renderer& renderer)
{
	SnakeNode* sn = m_head;
	int count = 0;
	while (sn != nullptr)
	{
		renderer.Draw(&sn->Get());
		sn = sn->next;
		count++;
	}
}

bool Snake::CheckCollision()
{
	SnakeNode* sn = m_head->next;
	while (sn != nullptr)
	{
		if (m_head->Get().getPosition() == sn->Get().getPosition())
		{
			return true;
		}
		sn = sn->next;
	}
	return false;
}

void Snake::Move(ap::Vec2f moveAmount, ap::TimeStep& ts)
{
	if (ts >= 1000.0f / TARGET_FPS)
	{
		ap::Vec2f prevpos = m_head->Get().getPosition();
		m_head->Get().move(moveAmount);
		
		float Xoffset = SnakeNode::s_size.x / 2.0f;
		float Yoffset = SnakeNode::s_size.y / 2.0f;

		if (m_head->Get().getPosition().x > WIDTH)
			m_head->Get().setPosition(ap::Vec2f(Xoffset, m_head->Get().getPosition().y));

		if (m_head->Get().getPosition().x < 0.0f)
			m_head->Get().setPosition(ap::Vec2f(WIDTH-Xoffset, m_head->Get().getPosition().y));

		if (m_head->Get().getPosition().y > HEIGHT)
			m_head->Get().setPosition(ap::Vec2f(m_head->Get().getPosition().x, Yoffset));

		if (m_head->Get().getPosition().y < 0.0f)
			m_head->Get().setPosition(ap::Vec2f(m_head->Get().getPosition().x, HEIGHT-Yoffset));

		if (m_head->next != nullptr)
		{
			SnakeNode* current = m_head->next;
			while (current != nullptr)
			{
				ap::Vec2f currentpos = current->Get().getPosition();
				current->Get().setPosition(prevpos);
				prevpos = currentpos;
				current = current->next;
			}
		}
		ts.Restart();
		if (CheckCollision())
		{
			clear();
			m_head = new SnakeNode(ap::Vec2f((WIDTH / 2.0f) + 20.0f, (HEIGHT / 2.0f) + 20.0f));
		}
	}
}

void Snake::clear()
{
	SnakeNode* sn = m_head;
	SnakeNode* prev;
	while (sn != nullptr)
	{
		prev = sn;
		sn = sn->next;
		delete prev;
	}
}

bool Snake::EatFood(ap::Vec2f foodPos)
{
	return m_head->Get().getPosition() == foodPos;
}

/// <summary>
///		SnakeNode Implementations
/// </summary>

const ap::Vec2f SnakeNode::s_size = ap::Vec2f(40.0f, 40.0f);

SnakeNode::SnakeNode()
{
	m_node.setSize(s_size);
	m_node.setColor(ap::Color::Red);
	next = nullptr;
	prev = nullptr;
}
SnakeNode::SnakeNode(ap::Vec2f pos)
{
	m_node.setPosition(pos);
	m_node.setSize(s_size);
	m_node.setColor(ap::Color::Red);
	next = nullptr;
	prev = nullptr;
}

ap::Quad& SnakeNode::Get()
{
	return m_node;
}