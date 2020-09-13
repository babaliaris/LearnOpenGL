#include "pch.h"
#include "TestScene.h"
#include "../../engine/Graphics/cube.h"
#include "../Components/TestComponent.h"
#include "../../engine/Graphics/Model.h"
#include "../../engine/Graphics/cube.h"
#include "../../engine/Graphics/LightGraphics.h"
#include "../../engine/DirectionalLight.h"
#include "../../engine/PointLight.h"

namespace Engine
{
    TestScene::TestScene(const std::string &name)
        : Scene(name)
    {
        
        Object* model = CREATE_MODEL(Model, "Assets/models/backpack/backpack.obj");
        model->transform.position = glm::vec3(4.0f, 0.0f, -2.0f);
        

        Object* cube = CREATE_OBJECT(Cube);

        
        DirectionalLight* dLight = (DirectionalLight*)CREATE_DIRECTIONAL_LIGHT(LightGraphics);
        dLight->transform.position = glm::vec3(0.0f, 2.0f, 4.0f);
        dLight->SetTarget(model->GetShader());

        
        
        PointLight* pLight0 = (PointLight*)CREATE_POINT_LIGHT(LightGraphics);
        pLight0->transform.position = glm::vec3(4.0f, 0.0f, -6.0f);
        pLight0->SetTarget(model->GetShader());
        pLight0->index = 0;

        PointLight* pLight1 = (PointLight*)CREATE_POINT_LIGHT(LightGraphics);
        pLight1->transform.position = glm::vec3(4.0f, 0.0f, 4.0f);
        pLight1->SetTarget(model->GetShader());
        pLight1->diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
        pLight1->index   = 1;
        
    }
}