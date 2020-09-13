#pragma once
#include "Light.h"

namespace Engine
{
	class DirectionalLight : public Light
	{

	public:
		DirectionalLight(Graphics* graphics);

		glm::vec3 direction = glm::vec3(0.0f, -1.0f, -1.0f);

		//Render Method.
		virtual void Render(glm::mat4& view, glm::mat4& proj) override;
	};
}

