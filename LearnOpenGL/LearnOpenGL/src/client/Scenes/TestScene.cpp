#include "pch.h"
#include "TestScene.h"
#include "../../engine/Graphics/cube.h"
#include "../Components/TestComponent.h"

namespace Engine
{
    TestScene::TestScene(const std::string &name)
        : Scene(name)
    {
        Object *obj = CREATE_OBJECT(Cube);
        obj->AddComponent(new TestComponent());
    }
}