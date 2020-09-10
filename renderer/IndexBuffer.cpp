#include "IndexBuffer.h"
#include <iostream>

IndexBuffer::IndexBuffer()
	: m_renderID(0)
{
	glGenBuffers(1, &m_renderID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 10000, nullptr, GL_STATIC_DRAW);
}
IndexBuffer::IndexBuffer(uint32_t* data, size_t size)
	: m_renderID(0)
{
	size_t count = size / 4;
	m_buffer.reserve(count);
	for (int i = 0; i < count; i++)
		m_buffer.push_back(data[i]);
	glGenBuffers(1, &m_renderID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, (const void*)m_buffer.data(), GL_STATIC_DRAW);
	//std::cout << __FILE__ << " " << glGetError() << " " << __LINE__ << std::endl;
}
void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID);
}
void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
uint32_t IndexBuffer::Count() const
{
	return m_buffer.size();
}
void IndexBuffer::updateIndicies(size_t numindicies)
{
	m_buffer.reserve(numindicies);
	switch (numindicies)
	{
	case ap::Entity::IndexCount::IndiciesQuad:
	{
		uint32_t index0 = m_maxIndex; m_maxIndex++;
		uint32_t index1 = m_maxIndex; m_maxIndex++;
		uint32_t index2 = m_maxIndex; m_maxIndex++;
		uint32_t index3 = m_maxIndex; m_maxIndex++;
		m_buffer.emplace_back(index0);
		m_buffer.emplace_back(index1);
		m_buffer.emplace_back(index3);
		m_buffer.emplace_back(index1);
		m_buffer.emplace_back(index2);
		m_buffer.emplace_back(index3);
	}
		break;
	case ap::Entity::IndexCount::IndiciesTriangle:
	{
		m_buffer.emplace_back(m_maxIndex); m_maxIndex++;
		m_buffer.emplace_back(m_maxIndex); m_maxIndex++;
		m_buffer.emplace_back(m_maxIndex); m_maxIndex++;
	}
		break;
	default :
		{		
			const size_t triangleCount = numindicies - 2;
			// This algorithm uses the number of triangles to be rendered rather than the number of indicies
			// the amount of triangles for any arbituary entity is always the number of verticies - 2
			// centerIdx is the first vertex to be rendered for each triangle and new triangles are formed from this vertex
			uint32_t centerIdx = m_maxIndex; m_maxIndex++;
			for (int i = 0; i < triangleCount; i++)
			{
				uint32_t index1 = m_maxIndex; m_maxIndex++;
				uint32_t index2 = m_maxIndex;
				m_buffer.push_back(centerIdx);
				m_buffer.push_back(index1);
				m_buffer.push_back(index2);
			}		
			m_maxIndex++;			
		}
		break;
	}	
	size_t size = sizeof(uint32_t) * m_buffer.size();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, (const void*)m_buffer.data());
	//std::cout << __FILE__ << " " << glGetError() << " " << __LINE__ << std::endl;
}
void IndexBuffer::clearIndexBuffer()
{
	m_buffer.clear();
	m_maxIndex = 0;
}