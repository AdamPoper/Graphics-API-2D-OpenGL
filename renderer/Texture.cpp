#include "AP2DGL/Texture.h"

namespace ap {

	Texture::Texture(const std::string& path)
		: m_filePath(path), m_width(0), m_height(0), m_bpp(0), m_buffer(nullptr)
	{
		stbi_set_flip_vertically_on_load(1);
		m_buffer = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_bpp, 4);  // 4 means RGBA		
		glGenTextures(1, &m_renderID);
		std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
		glBindTexture(GL_TEXTURE_2D, m_renderID);
		std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)m_buffer);
		std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
		glBindTexture(GL_TEXTURE_2D, 0);
		std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
		
	}
	Texture::Texture()
		: m_filePath(""), m_width(0), m_height(0), m_bpp(0), m_buffer(nullptr), m_renderID(0)
	{
	}
	void Texture::LoadFromFile(const char* file)
	{
		m_filePath = file;
		stbi_set_flip_vertically_on_load(1);
		m_buffer = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_bpp, 4);  // 4 means RGBA		
		glGenTextures(1, &m_renderID);
		std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
		glBindTexture(GL_TEXTURE_2D, m_renderID);
		std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)m_buffer);
		std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
		glBindTexture(GL_TEXTURE_2D, 0);
		std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
	}
	Texture::~Texture()
	{
		glDeleteTextures(1, &m_renderID);
		std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
		if (m_buffer != nullptr)
			stbi_image_free(m_buffer);
	}
	uint32_t Texture::TextureID() const { return m_renderID; }
	void Texture::Bind(uint32_t slot) const  // slot is optional
	{		
		glBindTexture(GL_TEXTURE_2D, m_renderID);
		glBindTextureUnit(slot, m_renderID);		
	}
	void Texture::UnBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
	}
}