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
		m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		m_texture = nullptr;
	}
	
	const size_t Quad::s_numIndicies  = 6;
	const size_t Quad::s_numVerticies = 4;
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
		m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	}
	void Quad::setColor(const Vec4f& color)
	{
		this->m_color = color;
		setData();
	}
	void Quad::setPosition(const Vec2f& pos)
	{
		this->m_position = pos;
		// manually set all the vertex positions based on the size
		setData();
	}
	void Quad::setSize(const Vec2f& size)
	{
		this->m_size = size;
		setData();
	}
	void Quad::setColor(const Vec3f& color)
	{
		m_color = { color.r, color.g, color.b, 1.0f }; // by default m_color alpha is 1.0f
		setData();
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

	size_t Quad::getNumIndicies()
	{
		return s_numIndicies;
	}
	size_t Quad::getNumVerticies()
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
	const glm::mat4& Entity::getModel() const
	{
		return m_model;
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
	const size_t Triangle::s_numIndicies  = 3;
	const size_t Triangle::s_numVerticies = 3;
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
		m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	}
	void Triangle::setColor(const Vec4f& color)
	{
		m_color = color;
		setData();
	}
	void Triangle::setColor(const Vec3f& color)
	{
		m_color = { color.r, color.g, color.b, 1.0f };
		setData();
	}
	void Triangle::setPosition(const Vec2f& pos)
	{
		m_position = pos;
		setData();
	}
	void Triangle::setSize(const Vec2f& size)
	{
		m_size = size;
		setData();
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
	size_t Triangle::getNumIndicies()  
	{
		return s_numIndicies;
	}
	size_t Triangle::getNumVerticies() 
	{
		return s_numVerticies;
	}
	const size_t Circle::s_numVerticies = 9;
	const size_t Circle::s_numIndicies  = 48;
	Circle::Circle()
		: m_radius(0.0f)
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
	void Circle::setPosition(const Vec2f& pos)
	{
		m_position = pos;
		setData();
	}
	void Circle::setColor(const Vec4f& color)
	{
		m_color = color;
		setData();
	}
	void Circle::setRadius(float r)
	{
		m_radius = r;
	}
	
	void Circle::setColor(const Vec3f& color)
	{
		m_color = Vec4f(color.r, color.g, color.b, 1.0f);
	}
	// a circle is just an array of triangles
	void Circle::setData()
	{
		
	}
	size_t Circle::getNumIndicies()
	{
		return s_numIndicies;
	}
	size_t Circle::getNumVerticies()
	{
		return s_numVerticies;
	}
}