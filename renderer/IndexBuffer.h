#pragma once
#include <GL/glew.h>
#include <vector>
#include "Entity.h"
class IndexBuffer
{
public:
	IndexBuffer();
	IndexBuffer(uint32_t* data, size_t size);
	void Bind() const;
	void UnBind() const;
	uint32_t Count() const;  // return number of indicies;
	void updateIndicies(size_t numIndices);
	void clearIndexBuffer();
private:
	std::vector<uint32_t> m_buffer;
	uint32_t m_renderID;
	uint32_t m_maxIndex = 0;
};