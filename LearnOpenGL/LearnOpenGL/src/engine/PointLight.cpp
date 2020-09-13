#include "pch.h"
#include "PointLight.h"
#include "Shader.h"

Engine::PointLight::PointLight(Graphics* graphics)
	: Light(graphics)
{
}

void Engine::PointLight::Render(glm::mat4& view, glm::mat4& proj)
{
	Light::Render(view, proj);

	std::stringstream ss;
	ss << "pLights[" << index << "]";
	std::string light = ss.str();

	//Has pLight = 1.
	target_shader->SetUniform("hasPLight", 1);
	
	//Set position.
	std::string light_pos = light + ".position";
	target_shader->SetUniform(light_pos.c_str(), transform.position);

	//Set Diffuse.
	std::string light_diffuse = light + ".diffuse";
	target_shader->SetUniform(light_diffuse.c_str(), diffuse);

	//Set Specular.
	std::string light_specular = light + ".specular";
	target_shader->SetUniform(light_specular.c_str(), specular);
}
