#include "AP2DGL/Camera.h"

namespace ap {

	void Camera::Translate(const Vec2f& translation)
	{
		m_translation.x += translation.x;
		m_translation.y += translation.y;
		m_translation.z = 0.0f;
	}
	const glm::vec3& Camera::GetTranslation() const
	{
		return m_translation;
	}
	const glm::mat4& Camera::GetTransform() const
	{
		return m_transform;
	}
	float Camera::GetRotation() const
	{
		return m_rotation;
	}
	Camera::Camera(const Camera& cam)
	{
		this->m_translation = cam.GetTranslation();
		this->m_transform = cam.GetTransform();
		this->m_rotation = cam.GetRotation();
	}
	void Camera::rotate(float degrees)
	{
		m_rotation += degrees;
	}
	void Camera::OnUpdate()
	{
		m_transform = glm::translate(glm::mat4(1.0f), m_translation)
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		//m_transform = glm::lookAt(glm::vec3(200.0f, 200.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	}
}