#include "renderer/Renderer.h"
#include <random>
#include <ctime>
#include <array>
#include <list>
#include <random>
#include <ctime>

#define WINDOW_WIDTH 1280.0f
#define WINDOW_HEIGHT 720.0f

bool checkCollision(const ap::Vec2f& bPos, const ap::Vec2f& aPos)
{
    if (bPos.x + 30.0f >= aPos.x)
        if (bPos.y >= aPos.y && bPos.y <= aPos.y + 50.0f)
            return true;   
    return false;
}
int main()
{    
    ap::Window mywindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test Game");

    ap::Clock playerClock, bulletsClock, bulletsDrawClock, alienClock, alienDrawClock;

    ap::Renderer renderer(&mywindow);
    ap::Texture backGroundTexture("res/textures/andromeda1.jpg");    
    ap::Texture playerTexture("res/textures/spaceship.png");
    ap::Texture alienTexture("res/textures/alien.png");
    ap::Quad backGround;
    backGround.setPosition(ap::Vec2f(0.0f, 0.0f));
    backGround.setSize(ap::Vec2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    backGround.setTexture(&backGroundTexture);   

    ap::Quad player;
    player.setPosition(ap::Vec2f(WINDOW_WIDTH * 0.06f, WINDOW_HEIGHT / 2.0f));
    player.setSize(ap::Vec2f(75.0f, 75.0f));
    player.setTexture(&playerTexture);
    
    std::list<ap::Quad> aliens;
    std::list<ap::Quad> bullets;    
    ap::Vec2f bulletSize = { 30.0f, 10.0f };          
    ap::Vec2f alienSize = { 50.0f, 50.0f };
    while (mywindow.isOpen())
    {              
        if (ap::Window::isKeyPressed(ap::key::AP_KEY_S) && playerClock.GetElapsedTimeAsMilliseconds() >= 7.0f)
        {
            if (player.getPosition().y <= WINDOW_HEIGHT - 75.0f)
                player.move(ap::Vec2f(0.0f, 6.0f));
            else
                player.move(ap::Vec2f(0.0f, -6.0f));
            playerClock.Restart();
        }
        if (ap::Window::isKeyPressed(ap::key::AP_KEY_W) && playerClock.GetElapsedTimeAsMilliseconds() >= 7.0f)
        {
            if (player.getPosition().y >= 0.0f)
                player.move(ap::Vec2f(0.0f, -6.0f));
            else
                player.move(ap::Vec2f(0.0f, 6.0f));
            playerClock.Restart();
        }
       if (ap::Window::isMouseButtonPressed(ap::mouseButton::AP_MOUSE_BUTTON_LEFT)        
            && bulletsClock.GetElapsedTimeAsMilliseconds() >= 200.0f)
        {            
            ap::Quad b;
            b.setColor(ap::Renderer::Color::Red);
            b.setPosition({ player.getPosition().x, player.getPosition().y + 35.0f });
            b.setSize(bulletSize);
            bullets.push_back(b);
            bulletsClock.Restart();
        }
        if (alienClock.GetElapsedTimeAsMilliseconds() >= 700.0f)
        {
            std::cout << "Spawing alien" << std::endl;
            ap::Quad alien;
            //srand(time(NULL));    no seeding neccessary
            float yPos = (float)(std::rand() % (int)(WINDOW_HEIGHT-50.0f));
            alien.setPosition(ap::Vec2f(WINDOW_WIDTH, yPos));
            alien.setSize(alienSize);
            alien.setTexture(&alienTexture);
            aliens.push_back(alien);
            alienClock.Restart();
        }
        for (auto bit = bullets.begin(); bit != bullets.end(); bit++)
           for (auto ait = aliens.begin(); ait != aliens.end(); ait++)
              if (checkCollision(bit->getPosition(), ait->getPosition()))
                 aliens.erase(ait);                                                              
        renderer.Draw(&backGround);
        if (!aliens.empty() && alienDrawClock.GetElapsedTimeAsMilliseconds() >= 20.0f)
        {
            if (aliens.begin()->getPosition().x <= -50.0f)
                aliens.pop_front();
            for (auto& a : aliens)
                a.move(ap::Vec2f(-10.0f, 0.0f));            
            alienDrawClock.Restart();
        }
        if (!bullets.empty() && bulletsDrawClock.GetElapsedTimeAsMilliseconds() >= 20.0f)
        {
            if (bullets.begin()->getPosition().x >= WINDOW_WIDTH)
                bullets.pop_front();            
            for (auto& b : bullets)
                b.move(ap::Vec2f(15.0f, 0.0f));                                   
            bulletsDrawClock.Restart();
        } 
        for (auto& a : aliens)
            renderer.Draw(&a);
        for (auto& b : bullets)
            renderer.Draw(&b);
        renderer.Draw(&player);
        renderer.onUpdate();
        mywindow.onUpdate();
    }    
}
