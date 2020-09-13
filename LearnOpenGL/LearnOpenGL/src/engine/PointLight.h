#pragma once
#include "Light.h"

namespace Engine
{
	class PointLight : public Light
	{

	public:

		int index		 = 0;
		float linear     = 0.1f;
		float quadtratic = 0.01f;

		PointLight(Graphics* graphics);

		virtual void Render(glm::mat4& view, glm::mat4 &proj) override;
	};
}

