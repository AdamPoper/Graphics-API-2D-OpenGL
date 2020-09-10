#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Vertex.h"
#include <string>
#include <iostream>

namespace ap {

#define MAX_KEYS		  512
#define MAX_MOUSE_BUTTONS 32
	class Window
	{
	public:
		Window();
		Window(float w, float h, const char* name);
		Window(const Window&) = delete;
		~Window();
		void onUpdate();
		bool isOpen() const;
		const Vec2f& getWindowSize() const;
		const Vec2f& getMousePosition() const;
		void setWindowSize(const Vec2f& size);
		static bool isKeyPressed(uint32_t keycode);
		static bool isMouseButtonPressed(uint32_t buttCode);
		float Width() const { return m_width; }
		float Height() const { return m_height; }
	private:
		float m_width, m_height;
		bool m_isOpen = false;
		Vec2f m_mousePos;
		GLFWwindow* m_window;
		std::string m_title;
		static bool s_keys[MAX_KEYS];
		static bool s_mouseButtons[MAX_MOUSE_BUTTONS];
		static friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	};
	
	enum key {
		AP_KEY_UNKOWN			= -1,
		AP_KEY_SPACE			= 32, 
		AP_KEY_APOSTROPHE		= 39,
		AP_KEY_COMMA			= 44,
		AP_KEY_MINUS			= 45,
		AP_KEY_PERIOD			= 46,
		AP_KEY_SLASH			= 47,
		AP_KEY_0				= 48,
		AP_KEY_1				= 49,
		AP_KEY_2				= 50,
		AP_KEY_3				= 51,
		AP_KEY_4				= 52,
		AP_KEY_5				= 53,
		AP_KEY_6				= 54,
		AP_KEY_7				= 55,
		AP_KEY_8				= 56,
		AP_KEY_9				= 57,
		AP_KEY_SEMICOLON		= 59,
		AP_KEY_EQUAL			= 61,
		AP_KEY_A				= 65,
		AP_KEY_B				= 66,
		AP_KEY_C				= 67,
		AP_KEY_D				= 68,
		AP_KEY_E				= 69,
		AP_KEY_F				= 70,
		AP_KEY_G				= 71,
		AP_KEY_H				= 72,
		AP_KEY_I				= 73,
		AP_KEY_J				= 74,
		AP_KEY_K				= 75,
		AP_KEY_L				= 76,
		AP_KEY_M				= 77,
		AP_KEY_N				= 78,
		AP_KEY_O				= 79,
		AP_KEY_P				= 80,
		AP_KEY_Q				= 81,
		AP_KEY_R				= 82,
		AP_KEY_S				= 83,
		AP_KEY_T				= 84,
		AP_KEY_U				= 85,
		AP_KEY_V				= 86,
		AP_KEY_W				= 87,
		AP_KEY_X				= 88,
		AP_KEY_Y				= 89,
		AP_KEY_Z				= 90,
		AP_KEY_LEFT_BRACKET     = 91,
		AP_KEY_BACKSLASH		= 92,
		AP_KEY_RIGHT_BRACKET	= 93,
		AP_KEY_ESCAPE			= 256,
		AP_KEY_ENTER			= 257,
		AP_KEY_TAB				= 258,
		AP_KEY_BACKSPACE		= 259,
		AP_KEY_INSERT			= 260,
		AP_KEY_DELETE			= 261,
		AP_KEY_RIGHT			= 262,
		AP_KEY_LEFT				= 263,
		AP_KEY_DOWN				= 264,
		AP_KEY_UP				= 265,
		AP_KEY_PAGE_UP			= 266,
		AP_KEY_PAGE_DOWN		= 267,
		AP_KEY_HOME				= 268,
		AP_KEY_END				= 269,
		AP_KEY_CAPS_LOCK		= 280,
		AP_KEY_SCROLL_LOCK		= 281,
		AP_KEY_NUM_LOCK			= 282,
		AP_KEY_PRINT_SCREEN		= 283,
		AP_KEY_PAUSE			= 284,
		AP_KEY_F1				= 290,
		AP_KEY_F2				= 291,
		AP_KEY_F3				= 292,
		AP_KEY_F4				= 293,
		AP_KEY_F5				= 294,
		AP_KEY_F6				= 295,
		AP_KEY_F7				= 296,
		AP_KEY_F8				= 297,
		AP_KEY_F9				= 298,
		AP_KEY_F10				= 299,
		AP_KEY_F11				= 300,
		AP_KEY_F12				= 301,
		AP_KEY_F13				= 302,
		AP_KEY_F14				= 303,
		AP_KEY_F15				= 304,
		AP_KEY_F16				= 305,
		AP_KEY_F17				= 306,
		AP_KEY_F18				= 307,
		AP_KEY_F19				= 308,
		AP_KEY_F20				= 309,
		AP_KEY_F21				= 310,
		AP_KEY_F22				= 311,
		AP_KEY_F23				= 312,
		AP_KEY_F24				= 313,
		AP_KEY_F25				= 314,
		AP_KEY_KP_0				= 320,
		AP_KEY_KP_1				= 321,
		AP_KEY_KP_2				= 322,
		AP_KEY_KP_3				= 323,
		AP_KEY_KP_4				= 324,
		AP_KEY_KP_5				= 325,
		AP_KEY_KP_6				= 326,
		AP_KEY_KP_7				= 327,
		AP_KEY_KP_8				= 328,
		AP_KEY_KP_9				= 329,
		AP_KEY_KP_DECIMAL		= 330,
		AP_KEY_KP_DIVIDE		= 331,
		AP_KEY_KP_MULTIPLY		= 332,
		AP_KEY_KP_SUBTRACT		= 333,
		AP_KEY_KP_ADD			= 334,
		AP_KEY_KP_ENTER			= 335,
		AP_KEY_KP_EQUAL			= 336,
		AP_KEY_LEFT_SHIFT		= 340,
		AP_KEY_LEFT_CONTROL		= 341,
		AP_KEY_LEFT_ALT			= 342,
		AP_KEY_LEFT_SUPER		= 343,
		AP_KEY_RIGHT_SHIFT		= 344,
		AP_KEY_RIGHT_CONTROL	= 345,
		AP_KEY_RIGHT_ALT		= 346,
		AP_KEY_RIGHT_SUPER		= 347,
		AP_KEY_MENU				= 348,
		AP_KEY_LAST				= AP_KEY_MENU
	};
	enum mouseButton
	{
		AP_MOUSE_BUTTON_1         = 0,
		AP_MOUSE_BUTTON_2         = 1,
		AP_MOUSE_BUTTON_3         = 2,
		AP_MOUSE_BUTTON_4         = 3,
		AP_MOUSE_BUTTON_5         = 4,
		AP_MOUSE_BUTTON_6         = 5,
		AP_MOUSE_BUTTON_7         = 6,
		AP_MOUSE_BUTTON_8         = 7,
		AP_MOUSE_BUTTON_LAST      = AP_MOUSE_BUTTON_8,
		AP_MOUSE_BUTTON_LEFT      = AP_MOUSE_BUTTON_1,
		AP_MOUSE_BUTTON_RIGHT     = AP_MOUSE_BUTTON_2,
		AP_MOUSE_BUTTON_MIDDLE    = AP_MOUSE_BUTTON_3
	};
}