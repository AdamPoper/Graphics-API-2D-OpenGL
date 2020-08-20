#include "Camera.h"

namespace ap {

	void Camera::Translate(const Vec2f& translation)
	{
		glm::vec3 trans = glm::vec3(translation.x, translation.y, 0.0f);
		m_translation = glm::translate(glm::mat4(1.0f), trans);
	}
	const glm::mat4& Camera::GetTranslation() const
	{
		return m_translation;
	}
	Camera::Camera(const Camera& cam)
	{
		this->m_translation = cam.GetTranslation();
	}
}