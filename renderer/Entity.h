#pragma once
#include "Vertex.h"
#include "Texture.h"
#include <vector>
#include <array>
#include <unordered_map>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <cmath>

class IndexBuffer;

namespace ap {

	class Entity
	{
	private:
		
	public:
		friend class IndexBuffer;
		friend class Renderer;
		friend class Quad;
		friend class Triangle;
		Entity();
		virtual ~Entity();   // always has a virtual destructor		
		void setPosition(const Vec2f& pos);
		void setColor(const Vec4f& color);
		void setColor(const Vec3f& color);
		void setSize(const Vec2f& size);
		virtual const size_t getNumIndicies()  = 0;
		virtual const size_t getNumVerticies() = 0;
		virtual void setTexture(Texture*);
		virtual void rotate(float degres)      = 0;
		virtual const Texture* getTexture() const;
		void move(const Vec2f& offset);		
		const Vec2f& getSize() const;
		const Vec2f& getPosition() const;
		const Vec4f& getColor() const;
		const Vertex* getData() const;	
		bool hasTexture() const;
	protected:
		virtual void setData() = 0;
		const float getTextureIndex() const;
		enum IndexCount {
			IndiciesTriangle = 3, IndiciesQuad = 6
		};
		enum VertexCount {
			VerticiesTriangle = 3, VerticiesQuad = 4
		};
	protected:
		std::vector<Vertex> m_verticies;
		// chaches the pointers to textures in case an entity has the same texture as another entity
		static std::unordered_map<Texture*, float> s_texturesCache;   
		float m_textureIndex;
		Vec2f m_position;
		Vec4f m_color;
		Vec2f m_size;
		Texture* m_texture;		
		static float s_nextTextureIndex;
		bool m_hasTexture = false;
	};
	class Quad : public Entity
	{
	public:
		Quad();			
		const size_t getNumIndicies()  override;
		const size_t getNumVerticies() override;
		void rotate(float degrees)     override {}
		static const size_t s_numIndicies;
		static const size_t s_numVerticies;
	private:
		void setData() override;
	};
	class Triangle : public Entity
	{
	public:
		Triangle();		
		const size_t getNumIndicies()  override;
		const size_t getNumVerticies() override;
		void rotate(float degrees)     override;
		static const size_t s_numIndicies;
		static const size_t s_numVerticies;
	private:
		Vertex& at(uint32_t vertexIndex);		
		void setData() override;
	};	
}
