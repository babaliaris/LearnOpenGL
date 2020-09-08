#include "pch.h"
#include "TestScene.h"
#include "../Graphics/cube.h"

namespace Engine
{
    TestScene::TestScene(const std::string &name)
        : Scene(name)
    {
        CREATE_OBJECT(Cube);
        CREATE_OBJECT(Cube);
        CREATE_OBJECT(Cube);
    }
}