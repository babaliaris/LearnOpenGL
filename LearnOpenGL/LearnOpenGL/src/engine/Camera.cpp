#include "pch.h"
#include "Camera.h"
#include "Core.h"
#include <glm/gtc/matrix_transform.hpp>


namespace Engine
{
	Camera* Camera::s_Instance = new Camera();
}


Engine::Camera::Camera()
	: m_worldUp(glm::vec3(0.0f, 1.0f, 0.0f)), m_position(glm::vec3(0.0f, 0.0f, 3.0f)), m_front(glm::vec3(0.0f, 0.0f, -1.0f))
{
	this->UpdateCoordSystem();
}





Engine::Camera::Camera(glm::vec3 pos)
	: m_worldUp(glm::vec3(0.0f, 1.0f, 0.0f)), m_position(pos), m_front(glm::vec3(0.0f, 0.0f, -1.0f))
{
	this->UpdateCoordSystem();
}





Engine::Camera::Camera(glm::vec3 pos, float yaw, float pitch)
	: m_pitch(pitch), m_yaw(yaw), m_worldUp(glm::vec3(0.0f, 1.0f, 0.0f)), m_position(pos), m_front(glm::vec3(0.0f, 0.0f, -1.0f))
{
	this->UpdateCoordSystem();
}





glm::mat4 Engine::Camera::GetView()
{
	return glm::lookAt(m_position, m_position + m_front, m_worldUp);
}





void Engine::Camera::Move(Movement movement, float speed)
{
	if (movement == Movement::FORWARD)
		m_position += m_front * speed;

	else if (movement == Movement::BACKWARD)
		m_position -= m_front * speed;

	else if (movement == Movement::LEFT)
		m_position -= m_right * speed;

	else if (movement == Movement::RIGHT)
		m_position += m_right * speed;

}




void Engine::Camera::Update(MouseMovedEvent& e)
{
	if (m_firstTime)
	{
		m_xoff = e.GetX();
		m_yoff = e.GetY();

		m_firstTime = false;
	}

	m_yaw   += (e.GetX() - m_xoff) * m_sensitivity;
	m_pitch += (m_yoff - e.GetY()) * m_sensitivity;

	m_xoff = e.GetX();
	m_yoff = e.GetY();


	if (m_pitch > 89.0f)
		m_pitch = 89.0f;

	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	glm::vec3 new_front = glm::vec3();

	new_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	new_front.y = sin(glm::radians(m_pitch));
	new_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	m_front = glm::normalize(new_front);

	this->UpdateCoordSystem();
}





void Engine::Camera::UpdateCoordSystem()
{
	this->m_right	= glm::normalize(glm::cross(m_front, m_worldUp));
	this->m_up		= glm::normalize(glm::cross(m_right, m_front));
}
