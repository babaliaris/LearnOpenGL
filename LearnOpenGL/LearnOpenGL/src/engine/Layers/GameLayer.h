#ifndef ENGINE_GAME_LAYER_H
#define ENGINE_GAME_LAYER_H
#include "../Layer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{

    class Application;

    class GameLayer : public Layer
    {
        public:
        GameLayer();

        virtual void OnAttach();
        virtual void OnDetach();
        virtual void OnUpdate();
        virtual void OnEvent(Event &e);

        private:
        Application& m_app;
        glm::mat4 m_view, m_proj;


    };
}

#endif