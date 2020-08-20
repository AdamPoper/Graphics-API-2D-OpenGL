#pragma once
#include <iostream>
#include <GL/glew.h>
typedef unsigned int uint32_t;
namespace ap {

	struct Vec2f
	{
		Vec2f() = default;
		Vec2f(float x, float y)
			: x(x), y(y) {}
		float x, y;
	};
	union Vec3f
	{
		Vec3f() = default;
		Vec3f(float x, float y, float z)
			: x(x), y(y), z(z) {}
		struct
		{
			float x, y, z;
		};
		struct
		{
			float r, g, b;
		};
	};
	union Vec4f
	{
		Vec4f() = default;
		Vec4f(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w) {}
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			float r, g, b, a;
		};
	};
	struct Vertex
	{
		Vec2f position;
		Vec4f color;
		Vec2f texCoords;
		float textureSlot;
		float hasTexture;
		static uint32_t CountFloats() {	return 6; }	
	};
}