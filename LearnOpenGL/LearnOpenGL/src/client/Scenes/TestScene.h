#ifndef ENGINE_TEST_SCENE_H
#define ENGINE_TEST_SCENE_H
#include "../../engine/Scene.h"

namespace Engine
{
    class TestScene : public Scene
    {
        public:
        TestScene(const std::string &name="TestScene");
    };
}

#endif