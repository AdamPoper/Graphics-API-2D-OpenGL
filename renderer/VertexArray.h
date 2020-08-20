#pragma once
#include <gl/glew.h>
#include <vector>
struct LayoutElement
{
	uint32_t count;
	uint32_t type;
	uint32_t normalized;

	static size_t getSizeOfType(uint32_t type)
	{
		switch (type)
		{
			case GL_FLOAT:         return 4;
			case GL_UNSIGNED_INT:  return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
	}
};
class VertexArray
{
public:
	VertexArray();
	template<typename T>
	void push(uint32_t count)
	{
		if (std::is_same_v<T, float>)
			m_elements.push_back({ count, GL_FLOAT, GL_FALSE });
		else if (std::is_same_v<T, uint32_t>)
			m_elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
		else if (std::is_same_v<T, unsigned char>)
			m_elements.push_back({ count, GL_UNSIGNED_BYTE, GL_FALSE });
		m_stride += sizeof(T) * count;
	}
	void Enable()
	{
		size_t offset = 0;
		for (int i = 0; i < m_elements.size(); i++)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, m_elements[i].count, m_elements[i].type, m_elements[i].normalized, m_stride, (const void*)offset);
			offset += m_elements[i].count * LayoutElement::getSizeOfType(m_elements[i].type);
		}
	}
private:
	uint32_t m_renderID;
	std::vector<LayoutElement> m_elements;
	size_t m_stride = 0;
};