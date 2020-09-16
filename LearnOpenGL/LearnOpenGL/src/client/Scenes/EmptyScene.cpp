#include "pch.h"
#include "EmptyScene.h"
#include "../../engine/Graphics/cube.h"
#include "../Components/TestComponent.h"
#include "../../engine/Graphics/Model.h"
#include "../../engine/Graphics/cube.h"
#include "../../engine/Graphics/LightGraphics.h"
#include "../../engine/DirectionalLight.h"
#include "../../engine/PointLight.h"

namespace Engine
{
    EmptyScene::EmptyScene(const std::string &name)
        : Scene(name)
    {
    }
}