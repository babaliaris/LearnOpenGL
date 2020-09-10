#ifndef ENGINE_GAME_LAYER_H
#define ENGINE_GAME_LAYER_H
#include "../Layer.h"
#include "../Events.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{

    class Application;
    class Camera;
    class Input;
    class Window;

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
        Camera& m_camera;
        Input& m_input;
        const Window& m_window;
        glm::mat4 m_view, m_proj;
        bool m_CursorDisabled = true;

        void OnMouseMoved(MouseMovedEvent &e);
        void OnKeyPress(KeyPressedEvent& e);
        void OnResize(WindowResizedEvent& e);


    };
}

#endif