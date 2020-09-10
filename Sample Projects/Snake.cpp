#include <AP2DGL/renderer/Renderer.h>
#include <AP2DGL/API_Tools/Clock.h>

#include <random>

#define WINDOW_WIDTH 800.0f
#define WINDOW_HEIGHT WINDOW_WIDTH
#define SWITCH_DIR_THRESH 100.0f

enum Directions
{
	UP, DOWN, LEFT, RIGHT
};

ap::Vec2f randomPosition(ap::Vec2f size)
{
	float x, y;
	srand(time(nullptr));
	int denom = (WINDOW_WIDTH / size.x) - 1;
	x = rand() % denom;
	y = rand() % denom;
	return { x, y };
}

bool collision(const std::vector<ap::Quad>& snake)
{
	for (int i = 1; i < snake.size(); i++)
		if (snake[0].getPosition() == snake[i].getPosition())
			return true;	
	return false;
}
void initSnake(std::vector<ap::Quad>& snake, ap::Quad* head, const ap::Vec2f& quadSize)
{
	// start with 3 ( the head and 2 more )
	float x = head->getPosition().x;
	for (int i = 0; i < 2; i++)
	{
		ap::Vec2f pos = { x,head->getPosition().y };
		ap::Quad q;
		q.setColor(ap::Color::White);
		q.setSize(quadSize);
		q.setPosition(pos);
		snake.push_back(q);
		x += quadSize.x;
	}
}

int main()
{
	ap::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Snake");
	ap::Renderer renderer(&window);
	ap::Vec2f quadSize = { 40.0f, 40.0f };
	ap::Quad head;  // not the actual head just a "template"
	head.setColor(ap::Color::White);
	head.setPosition(ap::Vec2f(700.0f, 300.0f));
	head.setSize(quadSize);
	ap::Clock moveClock;
	ap::Clock playerClock;
	bool wasd[4];
	wasd[Directions::UP]    = false;   // for determining direction
	wasd[Directions::DOWN]  = false;
	wasd[Directions::LEFT]  = true;
	wasd[Directions::RIGHT] = false;
	ap::Quad chaseQuad;	
	std::vector<ap::Quad> snakeQuads;
	snakeQuads.reserve(400); // 800 / 40 = 20 and 20 x 20 = 400
	snakeQuads.push_back(head);
	ap::Quad* snakeHead = &snakeQuads[0];
	std::vector<ap::Vec2f> positionHistory;   // for accessing the position history of the quads for moving them
	chaseQuad.setPosition(ap::Vec2f(quadSize.x/2.0f, quadSize.y/2.0f));
	auto r_pos = randomPosition(quadSize);
	chaseQuad.move(ap::Vec2f(quadSize.x * r_pos.x, quadSize.y * r_pos.y));
	chaseQuad.setColor(ap::Color::Red);
	chaseQuad.setSize(quadSize);
	ap::Quad next;  // the quad to used as a template for pushing back another quad
	next.setColor(ap::Color::White);
	next.setSize(quadSize);
	bool toIncrement = false;
	initSnake(snakeQuads, snakeHead, quadSize);
	while (window.isOpen())
	{		
		if (snakeHead->getPosition() == chaseQuad.getPosition())
		{
			toIncrement = true;
			bool okay = false;
			while (!okay)
			{
				okay = true;
				// next gets the position of the quad at the very back of the tail but does not get pushed back yet
				next.setPosition(snakeQuads.back().getPosition());
				chaseQuad.setPosition(ap::Vec2f(quadSize.x / 2.0f, quadSize.y / 2.0f));
				// chaseQuad ( Food ) gets a new position
				ap::Vec2f pos = randomPosition(quadSize);
				chaseQuad.move(ap::Vec2f(quadSize.x * pos.x, quadSize.y * pos.y));
				for (const auto& q : snakeQuads)
					if (q.getPosition() == chaseQuad.getPosition())
						okay = false;				
			}
		}
		
		if (moveClock.GetElapsedTimeAsMilliseconds() >= 180.0f)
		{			
			if (collision(snakeQuads))
			{
				snakeQuads.clear();
				snakeQuads.push_back(head);
				snakeHead = &snakeQuads[0];
				initSnake(snakeQuads, snakeHead, quadSize);
			}
			positionHistory.clear();
			positionHistory.reserve(snakeQuads.size());
			// get all the positions of the quads now
			for (int i = 0; i < snakeQuads.size(); i++)
				positionHistory.push_back(snakeQuads[i].getPosition());
			if (wasd[Directions::UP])			{	
				snakeHead->move(ap::Vec2f(0.0f, -quadSize.y)); 
				if (snakeHead->getPosition().y <= 0.0f)
					snakeHead->setPosition(ap::Vec2f(snakeHead->getPosition().x, WINDOW_HEIGHT-(quadSize.y/2.0f)));
			}
			else if (wasd[Directions::DOWN]) {
				snakeHead->move(ap::Vec2f(0.0f, quadSize.y));
				if (snakeHead->getPosition().y >= WINDOW_HEIGHT)
					snakeHead->setPosition(ap::Vec2f(snakeHead->getPosition().x, quadSize.y / 2.0f));
			}
			else if (wasd[Directions::LEFT]) {
				snakeHead->move(ap::Vec2f(-quadSize.x, 0.0f));
				if (snakeHead->getPosition().x <= 0.0f)
					snakeHead->setPosition(ap::Vec2f(WINDOW_WIDTH - (quadSize.y / 2.0f), snakeHead->getPosition().y));
			}
			else if (wasd[Directions::RIGHT]) {
				snakeHead->move(ap::Vec2f(quadSize.x, 0.0f));
				if (snakeHead->getPosition().x >= WINDOW_WIDTH)
					snakeHead->setPosition(ap::Vec2f(quadSize.x / 2.0f, snakeHead->getPosition().y));
			}
			// update the positions of all the quads with the position of the quad infront of it
			for (int i = 1; i < snakeQuads.size(); i++)  // start at 1 because the head was already moved
				snakeQuads[i].setPosition(positionHistory[i - 1]);  
					
			if (toIncrement)
			{
				snakeQuads.push_back(next);
				toIncrement = false;
			}
			moveClock.Restart();
		}
		if (playerClock.GetElapsedTimeAsMilliseconds() >= SWITCH_DIR_THRESH && ap::Window::isKeyPressed(ap::key::AP_KEY_W))
		{
			wasd[Directions::UP] = true;
			wasd[Directions::DOWN] = false;
			wasd[Directions::LEFT] = false;
			wasd[Directions::RIGHT] = false;
			playerClock.Restart();
		}
		if (playerClock.GetElapsedTimeAsMilliseconds() >= SWITCH_DIR_THRESH && ap::Window::isKeyPressed(ap::key::AP_KEY_D))
		{
			wasd[Directions::UP] = false;
			wasd[Directions::DOWN] = false;
			wasd[Directions::LEFT] = false;
			wasd[Directions::RIGHT] = true;
			playerClock.Restart();
		}
		if (playerClock.GetElapsedTimeAsMilliseconds() >= SWITCH_DIR_THRESH && ap::Window::isKeyPressed(ap::key::AP_KEY_A))
		{
			wasd[Directions::UP] = false;
			wasd[Directions::DOWN] = false;
			wasd[Directions::LEFT] = true;
			wasd[Directions::RIGHT] = false;
			playerClock.Restart();
		}
		if (playerClock.GetElapsedTimeAsMilliseconds() >= SWITCH_DIR_THRESH && ap::Window::isKeyPressed(ap::key::AP_KEY_S))
		{
			wasd[Directions::UP] = false;
			wasd[Directions::DOWN] = true;
			wasd[Directions::LEFT] = false;
			wasd[Directions::RIGHT] = false;
			playerClock.Restart();
		}
		for (int i = 0; i < snakeQuads.size(); i++)
			renderer.Draw(&snakeQuads[i]);
		renderer.Draw(&chaseQuad);
		renderer.onUpdate();
		window.onUpdate();
	}
}