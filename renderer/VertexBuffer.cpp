#include "VertexBuffer.h"
#include <iostream>
VertexBuffer::VertexBuffer()
	: m_renderID(0)
{
	glGenBuffers(1, &m_renderID);
	glBindBuffer(GL_ARRAY_BUFFER, m_renderID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 5000, nullptr, GL_DYNAMIC_DRAW);
	// make the gpu buffer fuck all huge to start
	std::cout << __FILE__ << " " << glGetError() << " " << __LINE__ << std::endl;
}
VertexBuffer::VertexBuffer(float* data, size_t size)
	: m_renderID(0)
{
	size_t count = size / 4;
	std::cout << "count: " << count << std::endl;
	//m_buffer.reserve(count / 2);
	for (int i = 0; i < count; i += ap::Vertex::CountFloats())
	{
		ap::Vec2f pos   = { data[i], data[i + 1] };
		ap::Vec4f color = { data[i + 2], data[i + 3], data[i + 4], data[i + 5] };
		ap::Vertex temp = { pos, color };
		m_buffer.push_back(temp);
	}
	glGenBuffers(1, &m_renderID);
	glBindBuffer(GL_ARRAY_BUFFER, m_renderID);
	glBufferData(GL_ARRAY_BUFFER, size, (const void*)m_buffer.data(), GL_DYNAMIC_DRAW);
}
void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_renderID);
}
void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
size_t VertexBuffer::Count() const
{
	return m_buffer.size();
}
const ap::Vertex* VertexBuffer::Data() const
{
	return m_buffer.data();
}
void VertexBuffer::addVertexData(const ap::Vertex* data, size_t num)
{
	m_buffer.reserve(num);
	for (int i = 0; i < num; i++)
		m_buffer.emplace_back(data[i]);
}
void VertexBuffer::setDynamicGeometry()
{
	size_t size = sizeof(ap::Vertex) * m_buffer.size();
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, (const void*)m_buffer.data());
	//std::cout << __FILE__ << " " << glGetError() << " " << __LINE__ << std::endl;
}
void VertexBuffer::clearVertexBuffer()
{
	m_buffer.clear();
}