#ifndef ENGINE_TEST_SCENE_H
#define ENGINE_TEST_SCENE_H
#include "../Scene.h"

namespace Engine
{
    class TestScene : public Scene
    {
        public:
        TestScene(const std::string &name="TestScene");
    };
}

#endif