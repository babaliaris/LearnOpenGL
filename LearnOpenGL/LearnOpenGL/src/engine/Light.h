#pragma once
#include "Object.h"

namespace Engine
{
	class Shader;

	class Light : public Object
	{

	public:
		Light(Graphics *graphics=nullptr);
		virtual ~Light();

		glm::vec3 ambient  = glm::vec3(0.1f, 0.1f, 0.1f);
		glm::vec3 diffuse  = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);

		inline void SetTarget(Shader* shader) { target_shader = shader; }

		//Render Method.
		virtual void Render(glm::mat4& view, glm::mat4& proj) override;

	protected:
		Shader* target_shader;
	};
}

