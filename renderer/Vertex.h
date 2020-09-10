#pragma once
#include <iostream>
#include <GL/glew.h>
#include "../glm/glm.hpp"

typedef unsigned int uint32_t;
namespace ap {

	using Vec2f = glm::vec2;
	using Vec3f = glm::vec3;
	using Vec4f = glm::vec4;
	
	struct Vertex
	{
		glm::vec2 position;
		glm::vec4 color;
		glm::vec2 texCoords;
		float textureSlot;
		float hasTexture;
		static uint32_t CountFloats() {	return 6; }	
	};

	struct Color
	{
		static Vec4f Blue;
		static Vec4f Red;
		static Vec4f Green;
		static Vec4f Cyan;
		static Vec4f Pink;
		static Vec4f Purple;
		static Vec4f White;
		static Vec4f Gray;
		static Vec4f Black;
		static Vec4f Yellow;
		static Vec4f Orange;
	};

}