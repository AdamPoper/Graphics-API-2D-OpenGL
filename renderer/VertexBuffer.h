#pragma once
#include <GL/glew.h>
#include <vector>
#include "Vertex.h"
class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(float* data, size_t size);
	void Bind() const;
	void UnBind() const;
	size_t Count() const; // return number of vertecies
	const ap::Vertex* Data() const; // return a pointer to the vertex data
	void addVertexData(const ap::Vertex* data, size_t num);
	void setDynamicGeometry();
	void clearVertexBuffer();
private:
	std::vector<ap::Vertex> m_buffer;
	uint32_t m_renderID;
};