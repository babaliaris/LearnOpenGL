#pragma once
#include "Engine.h"

class StencilLayer : public Engine::Layer
{
public:

    ~StencilLayer()
    {
    }

    void OnAttach() override
    {
        //Get App, Camera and the Window.
        m_app       = &Engine::Application::Get();
        m_camera    = &Engine::Camera::Get();
        m_window    = &m_app->GetWindow();

        //Create The Graphics To Be Rendered!!!
        m_cube      = new Engine::CubeSimple("CubeSimple", "");
        m_border    = new Engine::CubeBorder("CubeBorder", "");
    }

    void OnUpdate() override
    {
        //Create the Projection (Perspective) Matrix.
        m_proj = glm::perspective(glm::radians(45.0f), (float)m_window->GetWidth() / m_window->GetHeight(), 0.1f, 100.0f);

        glEnable(GL_DEPTH_TEST);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilMask(0xFF);
        m_cube->Render(glm::mat4(1.0f), m_camera->GetView(), m_proj);
        
        glStencilMask(0x00);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        //glDisable(GL_DEPTH_TEST);
        glm::mat4 border_model = glm::scale(glm::mat4(1.0f), glm::vec3(1.1f, 1.1f, 1.1f));
        m_border->Render(border_model, m_camera->GetView(), m_proj);

        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glEnable(GL_DEPTH_TEST);
    }


    void OnEvent(Engine::Event& e)
    {
    }


private:

    //This needs to be in every single layer!!!
    Engine::Application* m_app;
    Engine::Camera* m_camera;
    const Engine::Window* m_window;
    glm::mat4 m_proj;

    //Scene spesific stuff goes here!
    Engine::CubeSimple* m_cube;
    Engine::CubeBorder* m_border;



};

