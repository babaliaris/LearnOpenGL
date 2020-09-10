#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H
#include <glm/glm.hpp>
#include "Events.h"

namespace Engine
{
	enum class Movement
	{
		LEFT,
		RIGHT,
		FORWARD,
		BACKWARD
	};

	class Camera
	{

	public:

		Camera();
		Camera(glm::vec3 pos);
		Camera(glm::vec3 pos, float yaw, float pitch);

		glm::mat4 GetView();

		void Move(Movement movement, float speed);

		void Update(MouseMovedEvent &e);

		inline static Camera& Get() { return *s_Instance; }
		inline float GetSpeed() const { return m_speed; }

		inline void SetSensitivity(float value) { m_sensitivity = value; }
		inline void SetSpeedy(float value) { m_speed = value; }



	private:

		float m_speed		= 0.001f;
		float m_sensitivity = 0.2f;

		bool m_firstTime = true;
		float m_xoff	 = 0, m_yoff = 0;

		float m_pitch	= 0.0f;
		float m_yaw		= -90.0f;

		glm::vec3 m_worldUp;
		glm::vec3 m_position;
		glm::vec3 m_front;
		glm::vec3 m_right;
		glm::vec3 m_up;

		static Camera* s_Instance;


		void UpdateCoordSystem();

	};
}

#endif

