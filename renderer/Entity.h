#pragma once
#include "Vertex.h"
#include "Texture.h"
#include <vector>
#include <array>
#include <unordered_map>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <cmath>

class IndexBuffer;

enum EntityID {
	QUAD, TRIANGLE, CIRCLE, SPRITE, RENDER_ENTITY
};
// for the circle class
#define NUMBER_TRIANGLES 72

namespace ap {

	class Entity
	{		
	public:
		friend class IndexBuffer;
		friend class Renderer;
		friend class Quad;
		friend class Triangle;
		Entity();
		virtual ~Entity();   // always have a virtual destructor		
		void setPosition(const Vec2f& pos);
		void setColor(const Vec4f& color);
		void setColor(const Vec3f& color);
		void setSize(const Vec2f& size);
		virtual const size_t getNumIndicies()  = 0;
		virtual const size_t getNumVerticies() = 0;
		virtual void setTexture(Texture*);  // circles do not support textures because i don't feel like bothering to figure out how to do that
		virtual void rotate(float degres)      = 0;
		virtual const Texture* getTexture() const;
		void move(const Vec2f& offset);		
		const Vec2f& getSize() const;
		const Vec2f& getPosition() const;
		const Vec4f& getColor() const;
		const Vertex* getData() const;	
		bool hasTexture() const;
		EntityID Type() const;
	protected:
		virtual void setData() = 0;
		const float getTextureIndex() const;
		enum IndexCount {
			IndiciesTriangle = 3, IndiciesQuad = 6, IndiciesCircle = NUMBER_TRIANGLES * 3
		};
		enum VertexCount {
			VerticiesTriangle = 3, VerticiesQuad = 4, VerticiesCircle = NUMBER_TRIANGLES * 3
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
		EntityID m_type;
	};
	class Quad : public Entity
	{
	public:
		Quad();		
		Quad(const Vec2f& pos, const Vec2f& size, const Vec4f& color);
		Quad(const Vec2f& pos, const Vec2f& size, Texture* tex);
		const size_t getNumIndicies()  override;
		const size_t getNumVerticies() override;
		void rotate(float degrees)     override;
		bool setSubTexPoint(ap::Vec2f pos);
		bool setSubTexSize(ap::Vec2f size);
		static const size_t s_numIndicies;
		static const size_t s_numVerticies;		
	private:
		void applyTexCoords();
		void setData() override;		
		float m_rotation = 0.0f;	// expressed as degrees
		glm::vec2 m_texPos, m_texSize, m_originOffset;
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
		void setData() override;
		float m_rotation = 0.0f;   // expressed as degrees
	};	
	class Circle;
	class RenderTriangle : public Entity
	{
	public:
		friend class Circle;
		RenderTriangle();
		void setRadius(float r);
		void setVertex1Degrees(float v1d);
		void setVertex2Degrees(float v2d);
		void setVertexDegrees(float v1d, float v2d);
		const size_t getNumIndicies()  override;
		const size_t getNumVerticies() override;
		void rotate(float degrees)     override;
		static const size_t s_numIndicies;
		static const size_t s_numVerticies;
	private:
		void setData() override;
	private:
		float m_v1Degrees, m_v2Degrees;
		float m_radius;
	};
	
	// the only difference between Sprite and Quad is that Sprite automatically takes the size of the texture unless otherwise specified
	class Sprite : public Quad
	{
	public:
		Sprite() = default;
		Sprite(Texture*);		
		void setSpriteTexture(Texture* t);
	private:
		void update(Texture* t);
	};
	class RenderEntity : public Entity
	{
	public:
		friend class Renderer;
		RenderEntity() = default;
		RenderEntity(size_t verticies);
		RenderEntity(size_t verticies, float size);
		void setVertexCount(size_t verticies);
		void setRadius(float r);
		const size_t getNumIndicies()  override;
		const size_t getNumVerticies() override;
		void rotate(float degrees) override;
		void setVertexColor(uint32_t index, const Vec4f& c);
	private:
		void setData() override;
	private:
		size_t m_vertexCount = 0;		
		std::unordered_map<uint32_t, Vec4f> m_colorCache;		
	protected:
		float m_radius = 0;  // cause its like a circle with a varying amount of verticies	
		float m_rotation = 0.0f;
	};
	class Circle : public RenderEntity   // a circle is just a RenderEntity with a constant number of verticies
	{
	public:
		friend class Renderer;
		Circle();
		Circle(float radius);
		static const size_t MaxVerticies();
	private:
		static const size_t s_maxVertexCount;
	};
	class Point // basically just a Vertex
	{
	public: 
		Point();
		Point(const Vec2f& pos, const Vec4f& color);
		const Vec2f& GetPosition() const { return m_vertex.position; }
		const Vec4f& GetColor()    const { return m_vertex.color;    }
		const Vertex* Verticies()  const { return &m_vertex;         } 
	private:
		Vertex m_vertex;
	};
}