#include "pch.h"
#include "DirectionalLight.h"
#include "Shader.h"
#include "Camera.h"

Engine::DirectionalLight::DirectionalLight(Graphics* graphics)
	: Light(graphics)
{
}


void Engine::DirectionalLight::Render(glm::mat4& view, glm::mat4& proj)
{

	//Call default render method.
	Light::Render(view, proj);

	target_shader->SetUniform("hasDLight", 1);

	target_shader->SetUniform("dLight.direction", this->direction);
	target_shader->SetUniform("dLight.diffuse", this->diffuse);
	target_shader->SetUniform("dLight.specular", this->specular);

}
