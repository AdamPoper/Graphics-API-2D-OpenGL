#include "AP2DGL/Entity.h"

namespace ap {

	Entity::~Entity()
	{		
		delete[] m_outlineBuffer;
	}
	Entity::Entity()
	{
		m_size = { 0.0f, 0.0f };
		m_position = { 0.0f, 0.0f };
		m_color = { 1.0f, 1.0f, 1.0f, 1.0f };  // white by default		
		m_texture = nullptr;
		m_textureIndex = NULL;
		m_outlineBuffer = nullptr;
	}
	EntityID Entity::Type() const { return m_type; }
	
	float Entity::s_nextTextureIndex = 0.0f;
	std::unordered_map<Texture*, float> Entity::s_texturesCache;

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
	Vertex* Entity::getData()
	{
		return m_verticies.data();
	}
	const float Entity::getTextureIndex() const
	{
		return m_textureIndex;
	}
	Vertex& Entity::operator[](int index)
	{
		return m_verticies[index];
	}
	const Vertex& Entity::operator[](int index) const
	{
		return m_verticies[index];
	}
	float Entity::getOutLineSize() const
	{
		return m_outlineSize;
	}
	const ap::Vec4f& Entity::getOutLineColor() const
	{
		return m_outlineColor;
	}
	void Entity::setOutLineColor(const ap::Vec4f& color)
	{
		m_outlineColor = color;
	}
	void Entity::setOutLineSize(float size)
	{
		m_outlineSize = size;
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
	}
	void Entity::setColor(const Vec3f& c)
	{
		m_color = Vec4f(c.r, c.g, c.b, 1.0f);
	}
	void Entity::setColor(const Vec4f& c)
	{
		m_color = c;
	}
	void Entity::setSize(const Vec2f& s)
	{
		m_size = s;
	}
	void Entity::setPosition(const Vec2f& pos)
	{
		m_position = pos;		
	}

	/******QUAD IMPLEMENTAIONS*******/
	const size_t Quad::s_numIndicies = (const size_t)Entity::IndexCount::IndiciesQuad;
	const size_t Quad::s_numVerticies = (const size_t)Entity::VertexCount::VerticiesQuad;
	
	Quad::Quad()
	{
		m_verticies.reserve(s_numVerticies);
		for (int i = 0; i < s_numVerticies; i++)
			m_verticies.emplace_back(Vertex());
		m_size = { 0.0f, 0.0f };
		m_position = { 0.0f, 0.0f };
		m_color	  = { 1.0f, 1.0f, 1.0f, 1.0f };  // white by default		
		m_type	  = EntityID::QUAD;
		m_texPos  = { 0.0f, 0.0f };
		m_texSize = { 1.0f, 1.0f };
		m_texture = nullptr;
		m_outlineBuffer = new ap::Vertex[4];
		m_outlineColor  = ap::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
		m_outlineSize = 0.0f;
	}
	Quad::Quad(const Vec2f& pos, const Vec2f& size, const Vec4f& color)
	{
		this->m_position = pos;
		this->m_size = size;
		this->m_color = color;		
		m_verticies.reserve(s_numVerticies);
		for (int i = 0; i < s_numVerticies; i++)
			m_verticies.emplace_back(Vertex());
		m_type    = EntityID::QUAD;
		m_texPos  = { 0.0f, 0.0f };
		m_texSize = { 1.0f, 1.0f };
		m_texture = nullptr;
		m_outlineBuffer = new ap::Vertex[4];
		m_outlineColor = ap::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
		m_outlineSize = 0.0f;
	}
	Quad::Quad(const Vec2f& pos, const Vec2f& size, Texture* tex)
	{
		this->m_position = pos;
		this->m_size = size;
		this->m_texture = tex;
		this->m_hasTexture = true;
		m_verticies.reserve(s_numVerticies);
		for (int i = 0; i < s_numVerticies; i++)
			m_verticies.emplace_back(Vertex());		
		m_type    = EntityID::QUAD;
		m_texPos  = { 0.0f, 0.0f };
		m_texSize = { 1.0f, 1.0f };
		m_color   = ap::Color::White;
		m_outlineBuffer = new ap::Vertex[4];
		m_outlineColor = ap::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
		m_outlineSize = 0.0f;
	}	
	void Quad::setData()
	{
		for (auto& v : m_verticies)
		{
			v.color = m_color;
			v.textureSlot = m_textureIndex;
			v.hasTexture = m_hasTexture ? 1.0f : 0.0f;			
		}
		glm::mat4 transform;
		// if it is a perfect square then perform the matrix multiplication for rotation
		if(m_size.x == m_size.y)
		{
			transform = glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x, m_position.y, 1.0f))
				* glm::scale(glm::mat4(1.0f), glm::vec3(m_size.x, m_size.y, 1.0f))
				* glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		}			
		else // if not then dont do the rotation matrix math for the transform
		{
			transform = glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x, m_position.y, 1.0f))
				* glm::scale(glm::mat4(1.0f), glm::vec3(m_size.x, m_size.y, 1.0f));				
		}
		glm::vec4 positions[4];		
		positions[0] = { -0.5f,  0.5f, 0.0f, 1.0f };
		positions[1] = {  0.5f,  0.5f, 0.0f, 1.0f };
		positions[2] = {  0.5f, -0.5f, 0.0f, 1.0f };
		positions[3] = { -0.5f, -0.5f, 0.0f, 1.0f };

		for (int i = 0; i < s_numVerticies; i++)
			m_verticies[i].position = transform * positions[i];

		if (m_size.x != m_size.y) // if its a rectangle then rotate the verticies this way
		{		// I wasn't actually smart enough to have figured out the math for this
				// so I copied this from like stack overflow or something.
			    // I don't know how it works but somehow it does
			for (int i = 0; i < s_numVerticies; i++)
			{
				float theta = glm::radians(m_rotation);
				float x = m_verticies[i].position.x;
				float cx = m_position.x;
				float y = m_verticies[i].position.y;
				float cy = m_position.y;
				float tempX = x - cx;
				float tempY = y - cy;

				float rotatedX = tempX * cos(theta) - tempY * sin(theta);
				float rotatedY = tempX * sin(theta) + tempY * cos(theta);

				// translate back
				x = rotatedX + cx;
				y = rotatedY + cy;
				m_verticies[i].position.x = x;
				m_verticies[i].position.y = y;
			}			
		}
		applyTexCoords();		
		for (int i = 0; i < s_numVerticies; i++)
		{
			m_outlineBuffer[i].position = m_verticies[i].position;
			m_outlineBuffer[i].color = m_outlineColor;
		}
	}	
	float Quad::getRotation() const
	{
		return m_rotation;
	}
	bool Quad::setSubTexPoint(ap::Vec2f pos)
	{
		// returns true if conditions are met and the sample point gets updated
		// doing this prevents it from sampling from a point that's not in the texture
		glm::vec2 texSize;
		texSize.x = m_texSize.x * m_texture->Width();
		texSize.y = m_texSize.y * m_texture->Height();
		if ((pos.x + texSize.x <= m_texture->Width() && pos.y + texSize.y <= m_texture->Height())
			&& (pos.x >= 0.0f && pos.y >= 0.0f))
		{
			m_texPos.x = (pos.x / (float)m_texture->Width());
			m_texPos.y = (pos.y / (float)m_texture->Height());
			return true;
		}
		return false;
	}
	bool Quad::setSubTexSize(ap::Vec2f size)
	{
		// returns true if conditions are met and the sample point gets updated
		// doing this prevents it from showing anything that's not in the texture
		glm::vec2 texPos;
		texPos.x = m_texPos.x * m_texture->Width();
		texPos.y = m_texPos.y * m_texture->Height();
		if (size.x + texPos.x <= m_texture->Width() && size.y + texPos.y <= m_texture->Height())
		{
			m_texSize.x = (size.x / (float)m_texture->Width());
			m_texSize.y = (size.y / (float)m_texture->Height());
			return true;
		}
		return false;  
	}
	void Quad::applyTexCoords()
	{		
		m_verticies[0].texCoords.x = m_texPos.x;				
		m_verticies[0].texCoords.y = m_texPos.y;

		m_verticies[1].texCoords.x = m_texPos.x + m_texSize.x;
		m_verticies[1].texCoords.y = m_texPos.y;

		m_verticies[2].texCoords.x = m_texPos.x + m_texSize.x;
		m_verticies[2].texCoords.y = m_texPos.y + m_texSize.y;

		m_verticies[3].texCoords.x = m_texPos.x;
		m_verticies[3].texCoords.y = m_texPos.y + m_texSize.y;	
	}
	const size_t Quad::getNumIndicies()
	{
		return s_numIndicies;
	}
	const size_t Quad::getNumVerticies()
	{
		return s_numVerticies;
	}
	void Quad::rotate(float degrees)
	{
		m_rotation = degrees;
 	}
	
	/***********TRIANGLE IMPLEMENTATIONS***********/
	const size_t Triangle::s_numIndicies  = (const size_t)Entity::IndexCount::IndiciesTriangle;
	const size_t Triangle::s_numVerticies = (const size_t)Entity::VertexCount::VerticiesTriangle;
	Triangle::Triangle()
	{
		m_verticies.reserve(s_numVerticies);
		for (int i = 0; i < s_numVerticies; i++)
			m_verticies.emplace_back(Vertex());
		m_size     = { 0.0f, 0.0f };
		m_position = { 0.0f, 0.0f };
		m_color    = { 1.0f, 1.0f, 1.0f, 1.0f };  // white by default		
		m_type = EntityID::TRIANGLE;
	}
	float Triangle::getRotation() const
	{
		return m_rotation;
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
		m_verticies[1].position.x = (m_position.x + (m_size.x / 2.0f));
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
	
	void Triangle::rotate(float degrees)
	{
		m_rotation = degrees;
	}
	const size_t Triangle::getNumIndicies()  
	{
		return s_numIndicies;
	}
	const size_t Triangle::getNumVerticies() 
	{
		return s_numVerticies;
	}	

	/********RENDER TRIANGLE IMPLEMENTATIONS**********/

	const size_t RenderTriangle::s_numIndicies  = (const size_t)Entity::IndexCount::IndiciesTriangle;
	const size_t RenderTriangle::s_numVerticies = (const size_t)Entity::VertexCount::VerticiesTriangle;

	RenderTriangle::RenderTriangle()
		: m_v1Degrees(5.0f), m_v2Degrees(0.0f), m_radius(50.0f)   // defaults
	{
		m_position = { 0.0f, 0.0f };
		m_color = { 1.0f, 1.0f, 1.0f, 1.0f };  // white by default
		m_verticies.reserve(3);
		for (int i = 0; i < s_numVerticies; i++)
			m_verticies.push_back(Vertex());
		m_type = EntityID::TRIANGLE;
	}
	void RenderTriangle::setData()
	{
		for (auto& v : m_verticies)
		{
			v.color = m_color;
			v.textureSlot = m_textureIndex;
			v.hasTexture = m_hasTexture ? 1.0f : 0.0f;
		}
		m_verticies[0].position.x = m_position.x;
		m_verticies[0].position.y = m_position.y;
		m_verticies[1].position.x = m_position.x + (m_radius * cos(glm::radians(m_v1Degrees)));
		m_verticies[1].position.y = m_position.y + (m_radius * sin(glm::radians(m_v1Degrees)));
		m_verticies[2].position.x = m_position.x + (m_radius * cos(glm::radians(m_v2Degrees)));
		m_verticies[2].position.y = m_position.y + (m_radius * sin(glm::radians(m_v2Degrees)));
	}
	const size_t RenderTriangle::getNumIndicies()
	{
		return s_numIndicies;
	}
	const size_t RenderTriangle::getNumVerticies()
	{
		return s_numVerticies;
	}
	void RenderTriangle::setRadius(float r)
	{
		m_radius = r;
	}
	void RenderTriangle::setVertex1Degrees(float v1d)
	{
		m_v1Degrees = v1d;
	}
	void RenderTriangle::setVertex2Degrees(float v2d)
	{
		m_v1Degrees = v2d;		
	}
	void RenderTriangle::setVertexDegrees(float v1, float v2)
	{		
		m_v1Degrees = v1;
		m_v2Degrees = v2;
		if (m_v1Degrees >= 360.0f)
			m_v1Degrees -= 360.0f;
		if (m_v2Degrees >= 360.0f)
			m_v2Degrees -= 360.0f;		
	}
	void RenderTriangle::rotate(float d)
	{
		m_v1Degrees += d;
		m_v2Degrees += d;		
	}

	/*******Sprite Implementations********/
	Sprite::Sprite(Texture* t)
	{
		update(t);

		m_type = EntityID::SPRITE;
	}
	void Sprite::setSpriteTexture(Texture* t)
	{
		update(t);
	}
	void Sprite::update(Texture* t)
	{
		setTexture(t);
		setSize({ m_texture->Width(), m_texture->Height() });
	}
	/*******RenderEntity Implementations********/
	RenderEntity::RenderEntity(size_t verticies)
		: m_vertexCount(verticies), m_radius(0)
	{
		m_position = { 0.0f, 0.0f };
		m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
		m_type = EntityID::RENDER_ENTITY;
		m_verticies.reserve(m_vertexCount);
	}
	RenderEntity::RenderEntity(size_t verticies, float size)
		: m_vertexCount(verticies), m_radius(size)
	{
		m_position = { 0.0f, 0.0f };
		m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
		m_type = EntityID::RENDER_ENTITY;
		m_verticies.reserve(m_vertexCount);
	}
	void RenderEntity::setVertexCount(size_t verticies)
	{
		m_vertexCount = verticies;
		m_verticies.clear();
		m_verticies.reserve(m_vertexCount);
	}
	void RenderEntity::setRadius(float r)
	{
		m_radius = r;
	}
	void RenderEntity::rotate(float degrees)
	{
		m_rotation = degrees;
	}
	const size_t RenderEntity::getNumVerticies()
	{
		return m_vertexCount;
	}
	const size_t RenderEntity::getNumIndicies()
	{
		return m_vertexCount;   // its not the number of indicies it's the number of triangles, which is always the number of verticies-2    
	}
	void RenderEntity::setVertexColor(uint32_t index, const Vec4f& c)
	{
		m_colorCache[index] = c;
	}
	float RenderEntity::GetRadius() const { return m_radius; }
	void RenderEntity::setData()
	{
		// the verticies are created by using a center position, m_position, and like a circle, the position of the verticies are calculated with sin and cos
		// an indexing algorithm later determines which verticies should be rendered and when. 
		if (m_type == EntityID::CIRCLE)
			m_vertexCount = Circle::MaxVerticies();
		m_verticies.clear();
		m_verticies.reserve(m_vertexCount);
		float degrees = 0.0f;
		float next = 360.0f / (float)m_vertexCount;
		for (int i = 0; i < m_vertexCount; i++)
		{
			Vertex v;
			v.position.x = (m_radius * cos(glm::radians(degrees+m_rotation))) + m_position.x;
			v.position.y = (m_radius * sin(glm::radians(degrees+m_rotation))) + m_position.y;
			m_verticies.push_back(v);
			degrees += next;
		}
		for (Vertex& v : m_verticies)
		{			
			v.color = m_color;
			v.hasTexture = m_hasTexture;
			v.textureSlot = m_textureIndex;
		}
		for (auto& c : m_colorCache)
			m_verticies[c.first].color = c.second;		
	}
	/******Circle Implementations******/
	const size_t Circle::s_maxVertexCount = 32;
	Circle::Circle(float radius)
	{
		this->m_radius = radius;
		m_type = EntityID::CIRCLE;
	}
	Circle::Circle(const Vec2f& pos, float radius, const ap::Vec4f& color)
	{
		this->m_radius = radius;
		this->m_color = color;
		this->m_position = pos;
		m_type = EntityID::CIRCLE;
	}
	Circle::Circle()
	{
		this->m_radius = 0.0f;
		m_type = EntityID::CIRCLE;
	}
	const size_t Circle::MaxVerticies() { return s_maxVertexCount; }
}