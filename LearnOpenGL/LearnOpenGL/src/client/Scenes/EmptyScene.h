#ifndef ENGINE_TEST_SCENE_H
#define ENGINE_TEST_SCENE_H
#include "../../engine/Scene.h"

namespace Engine
{
    class EmptyScene : public Scene
    {
        public:
            EmptyScene(const std::string &name="EmptyScene");
    };
}

#endif