#include "pch.h"
#include "TestScene.h"
#include "../../engine/Graphics/cube.h"
#include "../Components/TestComponent.h"
#include "../../engine/Graphics/Model.h"

namespace Engine
{
    TestScene::TestScene(const std::string &name)
        : Scene(name)
    {
        //Object *obj = CREATE_OBJECT(Cube);
        //obj->AddComponent(new TestComponent());

        Object* model = CREATE_MODEL(Model, "Assets/models/backpack/backpack.obj");
        model->transform.position = glm::vec3(4.0f, 0.0f, -2.0f);
    }
}