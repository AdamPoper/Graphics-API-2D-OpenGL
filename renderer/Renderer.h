#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Window.h"
#include "Entity.h"
#include "Texture.h"
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
		void onUpdate();
		void addCamera(Camera* cam);
		void RemoveCamera();
		void SetRenderClearColor(const Vec3f& c) const;
		static struct Color
		{
			static Vec4f Blue;
			static Vec4f Red;
			static Vec4f Green;
			static Vec4f Yellow;
			static Vec4f Orange;
			static Vec4f Purple;
			static Vec4f Cyan;
			static Vec4f Pink;
			static Vec4f White;
			static Vec4f Gray;
			static Vec4f Black;
		};
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
		glm::mat4 m_MVP;
		glm::mat4 m_view;
		glm::mat4 m_projection;
		Texture* m_testTexture;
		Camera* m_camera;
		const Window* m_renderTarget;
	};
}