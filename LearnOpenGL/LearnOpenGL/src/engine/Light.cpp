#include "pch.h"
#include "Light.h"
#include "Shader.h"
#include "Camera.h"


Engine::Light::Light(Graphics* graphics)
	: Object(graphics)
{
}



Engine::Light::~Light()
{
}

void Engine::Light::Render(glm::mat4& view, glm::mat4& proj)
{
	Object::Render(view, proj);

	Camera& cam = Camera::Get();
	target_shader->SetUniform("ambient", this->ambient);
	target_shader->SetUniform("camPos", cam.GetPos());
}
