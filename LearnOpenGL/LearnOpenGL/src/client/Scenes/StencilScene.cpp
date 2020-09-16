#include "pch.h"
#include "StencilScene.h"
#include "../../engine/Graphics/CubeSimple.h"
#include "../../engine/Graphics/CubeBorder.h"
#include <glad/glad.h>

Engine::StencilScene::StencilScene(const std::string& name)
	: Scene(name)
{


	Engine::Object *cube = CREATE_OBJECT(Engine::CubeSimple);


	Engine::Object* border = CREATE_OBJECT(Engine::CubeBorder);
	border->transform.position = glm::vec3(3, 0, 0);
}
