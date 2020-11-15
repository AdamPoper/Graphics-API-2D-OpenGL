#pragma once
#include <Windows.h>
#include <commdlg.h>
#include <string>

#include "AP2DGL/Window.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace ap {
	
	class FileDialog
	{
	public:
		static std::string OpenFile(const char* filter, ap::Window* win);
		static std::string SaveFile(const char* filter, ap::Window* win);
		static const char* DefaultFileFilter;
	};
}