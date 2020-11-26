#pragma once

#include "Window.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Entity.h"
#include "Camera.h"
#include "stb_image/stb_image_write.h"
#include <assert.h>

namespace ap {
	enum class IMAGE_TYPE { JPG = 1, PNG = 2 };
	class Renderer
	{
	public:
		Renderer() = default;
		Renderer(const Window* window);
		Renderer(const Renderer&) = delete;  // no copy constructors allowed
		~Renderer();  // rendering components are heap allocated
		void Draw(Entity* ent);  // add entity vertex data		
		void Draw(const Vertex* verticies, size_t count, uint32_t primitive);  
		void onUpdate();
		void addCamera(Camera* cam);
		void RemoveCamera();
		void BindDefaultShader();
		void UnBindDefaultShader();
		glm::mat4 GetCurrentMVP() const;
		ShaderProgram* GetDefaultShader();
		void ClearRenderBuffer();
		void SetRenderClearColor(const Vec3f& c) const;	
		void DrawQuad(const Vec2f& pos, const Vec2f& size, const Vec4f& color);
		void DrawQuad(const Vec2f& pos, const Vec2f& size, Texture* tex);
		void DrawQuad(const Vec2f& pos, const Vec2f& size, const Vec4f& color, float degreesRotation);
		void DrawQuad(const Vec2f& pos, const Vec2f& size, Texture* tex, float degreesRotation);
		void DrawCircle(const Vec2f& pos, float radius, const ap::Vec4f& color);
		void DrawTriangle(const Vec2f& pos, const Vec2f& size, const ap::Vec4f& color);
		void DrawTriangle(const Vec2f& pos, const Vec2f& size, const ap::Vec4f& color, float degreesRotation);
		int ScreenShot(const char* filename);
		int ScreenShot(const char* filename, const ap::Vec2f& start, const ap::Vec2f& dimensions);
		int ScreenShot(const char* filename, const ap::Vec2f& start, const ap::Vec2f& dimensions, GLenum format, IMAGE_TYPE type);
	private:
		int SubmitPixelReadData(const char* filename, const ap::Vec2f& start, const ap::Vec2f& dimensions, GLenum format, size_t channelCount, IMAGE_TYPE type);
		void Blend() const;		
		void PrepareForRender();		
		friend class Entity;
	private:
		VertexArray m_vertexArray;
		VertexBuffer* m_vertexBuffer;
		IndexBuffer* m_indexBuffer;
		ShaderProgram* m_shaderProgram;
		static uint32_t s_referenceCounter;
		std::vector<Entity*> m_entities;		
		glm::mat4 m_MVP;
		glm::mat4 m_view;
		glm::mat4 m_projection;
		Texture* m_testTexture;
		Camera* m_camera;
		const Window* m_renderTarget;		
	};
	enum PRIMITIVES {
		LINES = GL_LINES,
		LINE_STRIP = GL_LINE_STRIP,
		LINE = GL_LINE,
		LINE_LOOP = GL_LINE_LOOP,
		TRIANGLES = GL_TRIANGLES,
		TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
		TRIANGLE_FAN = GL_TRIANGLE_FAN,
		QUADS = GL_QUADS,
		QUAD_STRIP = GL_QUAD_STRIP,
		POLYGON = GL_POLYGON,		
	};
	enum FORAMTS {
		RGB = GL_RGB,
		RGBA = GL_RGBA,
		BGRA = GL_BGRA,
		BGR = GL_BGR,
		RED = GL_RED,
		BLUE = GL_BLUE,
		GREEN = GL_GREEN,
		ALPHA = GL_ALPHA,
	};
	
}