#include "Entity.h"

namespace ap {

	Entity::~Entity()
	{
	}
	Entity::Entity()
	{
		m_size = { 0.0f, 0.0f };
		m_position = { 0.0f, 0.0f };
		m_color = { 1.0f, 1.0f, 1.0f, 1.0f };  // white by default		
		m_texture = nullptr;
		m_textureIndex = NULL;
	}
	
	const size_t Quad::s_numIndicies = (const size_t)Entity::IndexCount::IndiciesQuad;
	const size_t Quad::s_numVerticies = (const size_t)Entity::VertexCount::VerticiesQuad;
	float Entity::s_nextTextureIndex = 0.0f;
	std::unordered_map<Texture*, float> Entity::s_texturesCache;
	Quad::Quad()
	{
		m_verticies.reserve(s_numVerticies);
		for (int i = 0; i < s_numVerticies; i++)
		{
			Vertex temp;
			m_verticies.emplace_back(temp);
		}
		m_size = { 0.0f, 0.0f };
		m_position = { 0.0f, 0.0f };
		m_color = { 1.0f, 1.0f, 1.0f, 1.0f };  // white by default		
	}
	
	void Quad::setData()
	{
		for (auto& v : m_verticies)
		{
			v.color = m_color;
			v.textureSlot = m_textureIndex;		
			v.hasTexture = m_hasTexture ? 1.0f : 0.0f;
			//std::cout << "Texture slot: " << v.textureSlot << std::endl;
		}
		m_verticies[0].position.x = m_position.x;
		m_verticies[0].position.y = m_position.y;
		m_verticies[1].position.x = m_position.x + m_size.x;
		m_verticies[1].position.y = m_position.y;
		m_verticies[2].position.x = m_position.x + m_size.x;
		m_verticies[2].position.y = m_position.y + m_size.y;
		m_verticies[3].position.x = m_position.x;
		m_verticies[3].position.y = m_position.y + m_size.y;

		m_verticies[0].texCoords.x = 0.0f;
		m_verticies[0].texCoords.y = 1.0f;
		m_verticies[1].texCoords.x = 1.0f;
		m_verticies[1].texCoords.y = 1.0f;
		m_verticies[2].texCoords.x = 1.0f;
		m_verticies[2].texCoords.y = 0.0f;
		m_verticies[3].texCoords.x = 0.0f;
		m_verticies[3].texCoords.y = 0.0f;		
	}

	const size_t Quad::getNumIndicies()
	{
		return s_numIndicies;
	}
	const size_t Quad::getNumVerticies()
	{
		return s_numVerticies;
	}
	const Vec4f& Entity::getColor() const
	{
		return m_color;
	}
	const Vec2f& Entity::getSize() const
	{
		return m_size;
	}
	const Vec2f& Entity::getPosition() const
	{
		return m_position;
	}
	const Vertex* Entity::getData() const
	{
		return m_verticies.data();
	}
	
	const float Entity::getTextureIndex() const
	{
		return m_textureIndex;
	}	
	void Entity::setTexture(Texture* tex)
	{
		if (s_texturesCache.find(tex) == s_texturesCache.end())
		{
			std::cout << "Texture not chached" << std::endl;
			s_texturesCache[tex] = s_nextTextureIndex;		
			m_texture = tex;
			m_textureIndex = s_nextTextureIndex;		
			s_nextTextureIndex = s_nextTextureIndex != 32 ? s_nextTextureIndex + 1 : s_nextTextureIndex;
			m_hasTexture = true;			
		}
		else
		{		
			std::cout << "Texture already chached assigning texture slot" << std::endl;
			m_texture = tex;
			m_textureIndex = s_texturesCache[tex];
			m_hasTexture = true;			
		}
	}
	const Texture* Entity::getTexture() const
	{
		return m_texture;
	}
	bool Entity::hasTexture() const
	{
		return m_hasTexture;
	}
	void Entity::move(const Vec2f& offset)
	{
		m_position.x += offset.x;
		m_position.y += offset.y;
		setData();
	}
	void Entity::setColor(const Vec3f& c)
	{
		m_color = Vec4f(c.r, c.g, c.b, 1.0f);
		setData();
	}
	void Entity::setColor(const Vec4f& c)
	{
		m_color = c;
		setData();
	}
	void Entity::setSize(const Vec2f& s)
	{
		m_size = s;
		setData();
	}
	void Entity::setPosition(const Vec2f& pos)
	{
		m_position = pos;
		setData();
	}
	const size_t Triangle::s_numIndicies = (const size_t)Entity::IndexCount::IndiciesTriangle;
	const size_t Triangle::s_numVerticies = (const size_t)Entity::VertexCount::VerticiesTriangle;
	Triangle::Triangle()
	{
		m_verticies.reserve(s_numVerticies);
		for (int i = 0; i < s_numVerticies; i++)
		{
			Vertex temp;
			m_verticies.emplace_back(temp);
		}
		m_size     = { 0.0f, 0.0f };
		m_position = { 0.0f, 0.0f };
		m_color    = { 1.0f, 1.0f, 1.0f, 1.0f };  // white by default
		//m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	}
	
	void Triangle::setData()
	{
		for (auto& v : m_verticies)
		{
			v.color = m_color;
			v.textureSlot = m_textureIndex;
			v.hasTexture  = m_hasTexture ? 1.0f : 0.0f;
		}
		m_verticies[0].position.x = m_position.x;
		m_verticies[0].position.y = m_position.y;
		m_verticies[1].position.x = m_position.x + (m_size.x / 2.0f);
		m_verticies[1].position.y = m_position.y + m_size.y;
		m_verticies[2].position.x = m_position.x - (m_size.x / 2.0f);
		m_verticies[2].position.y = m_position.y + m_size.y;
		
		m_verticies[0].texCoords.x = 0.5f;
		m_verticies[0].texCoords.y = 1.0f;
		m_verticies[1].texCoords.x = 1.0f;
		m_verticies[1].texCoords.y = 0.0f;
		m_verticies[2].texCoords.x = 0.0f;
		m_verticies[2].texCoords.y = 0.0f;
	}
	Vertex& Triangle::at(uint32_t index)
	{
		// assert
		return m_verticies[index];
	}
	void Triangle::rotate(float degrees)
	{
		float radius = 0.0f;
		float angleVertex1 = 0.0f;
		float angleVertex2 = 0.0f;
		{
			float b = (m_verticies[0].position.x - m_verticies[1].position.x);
			float a = (m_verticies[0].position.y - m_verticies[1].position.y);
			radius = (sqrt(powf(a, 2) + powf(b, 2)));
			std::cout << "radius: " << radius << std::endl;
			angleVertex1 = asin(a / radius) * (180.0f / 3.14159f);
			std::cout << "Angle vertex 1: " << angleVertex1 << std::endl;
		}
		{
			float b = (m_verticies[0].position.x - m_verticies[2].position.x);
			float a = (m_verticies[0].position.y - m_verticies[2].position.y);			
			angleVertex2 = asin(a / radius) * (180.0f / 3.14159f);
			std::cout << "Angle vertex 2: " << angleVertex2 << std::endl;
		}
	}
	const size_t Triangle::getNumIndicies()  
	{
		return s_numIndicies;
	}
	const size_t Triangle::getNumVerticies() 
	{
		return s_numVerticies;
	}	
}
