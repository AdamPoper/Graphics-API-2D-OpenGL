#pragma once

#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/glm.hpp"
#include "Vertex.h"
namespace ap {

	class Camera
	{
	public:
		friend class Renderer;
		Camera() = default;
		Camera(const Camera& cam);
		void Translate(const Vec2f& trans);
	private:
		const glm::mat4& GetTranslation() const;
		glm::mat4 m_translation;
	};
}