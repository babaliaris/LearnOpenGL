#ifndef ENGINE_CUBE_SIMPLE_H
#define ENGINE_CUBE_SIMPLE_H
#include "../Graphics.h"

namespace Engine
{
    class CubeSimple : public Graphics
    {
        public:
            CubeSimple(const std::string &name, const std::string& path);
    };
}

#endif