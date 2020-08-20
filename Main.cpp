#include "renderer/Renderer.h"
#include <random>
#include <ctime>
#include <array>

int main()
{
    
    ap::Window mywindow(1280, 720, "Window");

    ap::Renderer renderer(&mywindow);

    ap::Texture texture("res/textures/bird.png");
    ap::Texture earth("res/textures/earth.png");
    ap::Texture king("res/textures/king.png");
    
    //ap::Circle circle;
    //circle.setColor(ap::Renderer::Color::Red);
    //circle.setPosition({ 340.0f, 270.0f });
    //circle.setRadius(30.0f);

    ap::Quad quad;
    quad.setPosition(ap::Vec2f(600.0f, 400.0f));
    quad.setSize({100.0f, 130.0f});
    quad.setColor(ap::Renderer::Color::Cyan);

    ap::Triangle tri;
    tri.setColor(ap::Renderer::Color::Green);
    tri.setPosition({ 400.0f, 350.0f });
    tri.setSize({ 120.0f, 70.0f });

    while (mywindow.isOpen())
    {          
        if (ap::Window::isKeyPressed(ap::AP_KEY_SPACE))
            tri.rotate(45.0f);
        renderer.Draw(&quad);
        renderer.Draw(&tri);
        renderer.onUpdate();
        mywindow.onUpdate();      
    }
    
}