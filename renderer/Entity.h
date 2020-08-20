#pragma once
#include "Vertex.h"
#include "Texture.h"
#include <vector>
#include <array>
#include <unordered_map>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <cmath>

#define CIRCLE_TRIANGLES 16

namespace ap {

	class Entity
	{
	public:
		friend class Renderer;
		Entity();
		virtual ~Entity();
		// TODO there's no reason these have to be virtual will be changed later
		virtual void setPosition(const Vec2f& pos) = 0;
		virtual void setColor(const Vec4f& color)  = 0;
		virtual void setColor(const Vec3f& color)  = 0;
		virtual void setSize(const Vec2f& size)    = 0;
		virtual size_t getNumIndicies()            = 0;
		virtual size_t getNumVerticies()           = 0;
		virtual void setTexture(Texture*);
		virtual void rotate(float degres)          = 0;
		virtual const Texture* getTexture() const;
		void move(const Vec2f& offset);
		const glm::mat4& getModel() const;
		const Vec2f& getSize() const;
		const Vec2f& getPosition() const;
		const Vec4f& getColor() const;
		const Vertex* getData() const;	
		bool hasTexture() const;
	protected:
		virtual void setData() = 0;
		const float getTextureIndex() const;
	protected:
		std::vector<Vertex> m_verticies;
		// chaches the pointers to textures in case an entity has the same texture as another entity
		static std::unordered_map<Texture*, float> s_texturesCache;   
		float m_textureIndex;
		Vec2f m_position;
		Vec4f m_color;
		Vec2f m_size;
		Texture* m_texture;
		glm::mat4 m_model;
		static float s_nextTextureIndex;
		bool m_hasTexture = false;
	};
	class Quad : public Entity
	{
	public:
		Quad();
		void setPosition(const Vec2f& pos) override;
		void setColor(const Vec4f& color)  override;
		void setColor(const Vec3f& color)  override;
		void setSize(const Vec2f& size)    override;		
		size_t getNumIndicies()            override;
		size_t getNumVerticies()           override;
		void rotate(float degrees)         override {}
		static const size_t s_numIndicies;
		static const size_t s_numVerticies;
	private:
		void setData() override;
	};
	class Triangle : public Entity
	{
	public:
		Triangle();
		void setPosition(const Vec2f& pos) override;
		void setColor(const Vec4f& color)  override;
		void setColor(const Vec3f& color)  override;
		void setSize(const Vec2f& size)    override;		
		size_t getNumIndicies()			   override;
		size_t getNumVerticies()		   override;
		void rotate(float degrees)         override;
		static const size_t s_numIndicies;
		static const size_t s_numVerticies;
	private:
		Vertex& at(uint32_t vertexIndex);		
		void setData() override;

	};
	class Circle : public Entity
	{
	public:
		Circle();
		void setPosition(const Vec2f& pos) override;
		void setColor(const Vec4f& color)  override;
		void setColor(const Vec3f& color)  override;
		void setSize(const Vec2f& size)    override {}  // will not be used so no reason to be virtual i'm just retarded
		void setRadius(float radius);
		void rotate(float degrees)         override {}
	    size_t getNumIndicies()			   override;
	    size_t getNumVerticies()		   override;
		static const size_t s_numIndicies;
		static const size_t s_numVerticies;
	private:
		void setData() override;
		float degreesToRadians(float deg) { return (deg * (3.14159f / 180.0f)); }
		float m_radius;
		std::array<Triangle, CIRCLE_TRIANGLES> m_triangles;
	};	
}