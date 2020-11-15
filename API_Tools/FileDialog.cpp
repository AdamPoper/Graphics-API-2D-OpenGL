#include "FileDialog.h"

namespace ap {
	const char* FileDialog::DefaultFileFilter = "Text Files\0*.txt\0Any File\0*.*\0";
	std::string FileDialog::OpenFile(const char* filter, ap::Window* win)
	{
		OPENFILENAMEA ofn;
		CHAR szFile[_MAX_PATH] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)win->glfw_ptr());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetOpenFileNameA(&ofn))
		{
			return ofn.lpstrFile;
		}
		return std::string();
	}
	std::string FileDialog::SaveFile(const char* filter, ap::Window* win)
	{
		OPENFILENAMEA ofn;
		CHAR szFile[_MAX_PATH] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)win->glfw_ptr());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetSaveFileNameA(&ofn))
		{
			return ofn.lpstrFile;
		}
		return std::string();
	}
}