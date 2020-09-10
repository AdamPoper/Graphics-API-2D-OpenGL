#pragma once
#include <GL/glew.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include "../stb_image/stb_image.h"
namespace ap {
	
	class Texture
	{
	public:
		Texture(const std::string& file);
		~Texture();
		friend class Renderer;
		friend class Entity;
		inline int Width()  { return m_width; }
		inline int Height() { return m_height; }
	private:
		void Bind(uint32_t slot = 0) const;
		void UnBind() const;
	private:
		uint32_t m_renderID;
		std::string m_filePath;
		unsigned char* m_buffer;
		int m_width, m_height, m_bpp;		
	};
}