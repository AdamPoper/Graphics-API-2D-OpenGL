#pragma once

#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "Vertex.h"
namespace ap {

	class Camera
	{
	public:
		friend class Renderer;
		Camera() = default;
		Camera(const Camera& cam);
		void Translate(const Vec2f& trans);
		void rotate(float r);
	private:
		const glm::vec3& GetTranslation() const;
		const glm::mat4& GetTransform() const;
		float GetRotation() const;
		void OnUpdate();
		glm::vec3 m_translation;
		glm::mat4 m_transform;
		glm::vec3 m_camerPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		float m_rotation = 0.0f;
	};
}