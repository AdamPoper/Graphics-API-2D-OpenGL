#include "AP2DGL/VertexArray.h"
#include <iostream>
VertexArray::VertexArray()
	: m_renderID(0)
{
	glGenVertexArrays(1, &m_renderID);
	glBindVertexArray(m_renderID);
}