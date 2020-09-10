#include "Window.h"

namespace ap {
	bool Window::s_keys[MAX_KEYS];
	bool Window::s_mouseButtons[MAX_MOUSE_BUTTONS];
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->s_keys[key] = action != GLFW_RELEASE;		
	}
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->s_mouseButtons[button] = action != GLFW_RELEASE;
	}
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_mousePos.x = xpos;
		win->m_mousePos.y = ypos;
	}
	Window::Window()
		: m_width(0), m_height(0), m_title(), m_window(nullptr)
	{
	}
	Window::Window(float w, float h, const char* name)
		: m_width(w), m_height(h), m_title(name), m_window(nullptr)
	{
		/* Initialize the library */
		if (!glfwInit())
			return;
		
		else std::cout << "GLFW Init" << std::endl;
		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
		if (!m_window)
		{
			glfwTerminate();
			std::cout << "Terminated GLFW" << std::endl;
			return;
		}
		else
		{
			m_isOpen = true;
			std::cout << "GLFW Window Good" << std::endl;
		}
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, this);
		glfwSetKeyCallback(m_window, key_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);
		glfwSetCursorPosCallback(m_window, cursor_position_callback);		
		if (glewInit() == GLEW_OK)
			std::cout << "Glew OK!" << std::endl;
		else
			std::cout << "Glew Not OK!" << std::endl;		
		for (int i = 0; i < MAX_KEYS; i++)
			s_keys[i] = false;
		for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
			s_mouseButtons[i] = false;
	}
	Window::~Window()
	{
		glfwTerminate();
	}
	void Window::onUpdate()
	{
		int w, h;
		glfwGetWindowSize(m_window, &w, &h);
		m_width = (float)w; m_height = (float)h;
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
	bool Window::isOpen() const
	{
		return !glfwWindowShouldClose(m_window);
	}
	const Vec2f& Window::getWindowSize() const
	{
		return { m_width, m_height };
	}
	const Vec2f& Window::getMousePosition() const
	{
		return m_mousePos;
	}
	void Window::setWindowSize(const Vec2f& size)
	{
		m_width  = size.x;
		m_height = size.y;
		glfwSetWindowSize(m_window, (int)m_width, (int)m_height);
	}
	bool Window::isMouseButtonPressed(uint32_t buttCode)
	{
		if (buttCode > MAX_MOUSE_BUTTONS)
			return false;
		return s_mouseButtons[buttCode];
	}
	bool Window::isKeyPressed(uint32_t keycode)
	{
		if (keycode > MAX_KEYS)
			return false;
		return s_keys[keycode];
	}
}