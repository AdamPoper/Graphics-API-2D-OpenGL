#pragma once

#include "Window.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Entity.h"
#include "Camera.h"
#include <assert.h>

namespace ap {

	class Renderer
	{
	public:
		Renderer() = default;
		Renderer(const Window* window);
		Renderer(const Renderer&) = delete;  // no copy constructors allowed
		~Renderer();  // rendering components are heap allocated
		void Draw(Entity* ent);  // add entity vertex data
		void Draw(Point* p);     // add point vertex data		
		void Draw(const Vertex* verticies, size_t count, uint32_t primitive);
		void onUpdate();
		void addCamera(Camera* cam);
		void RemoveCamera();
		void SetRenderClearColor(const Vec3f& c) const;	
		void DrawQuad(const Vec2f& pos, const Vec2f& size, const ap::Vec4f& color);
		void DrawQuad(const Vec2f& pos, const Vec2f& size, Texture* tex);
		void DrawCircle(const Vec2f& pos, float radius, const ap::Vec4f& color);
	private:
		void Blend() const;		
		friend class Entity;
	private:
		VertexArray m_vertexArray;
		VertexBuffer* m_vertexBuffer;
		IndexBuffer* m_indexBuffer;
		ShaderProgram* m_shaderProgram;
		static uint32_t s_referenceCounter;
		std::vector<Entity*> m_entities;		
		std::vector<Entity*> m_memAllocEnts;   // a vector of points to entities that were heap allocated so the can be properly deleted
		std::vector<Point*>  m_points;  // separate vector for points because they use a different drawing primitive		
		glm::mat4 m_MVP;
		glm::mat4 m_view;
		glm::mat4 m_projection;
		Texture* m_testTexture;
		Camera* m_camera;
		const Window* m_renderTarget;
	};
}