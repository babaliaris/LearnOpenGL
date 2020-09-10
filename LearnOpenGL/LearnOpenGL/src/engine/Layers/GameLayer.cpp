#include "pch.h"
#include "GameLayer.h"
#include "../Application.h"
#include "../Scene.h"
#include "../Window.h"
#include "../Camera.h"
#include "../Input.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{

    GameLayer::GameLayer()
        : m_app(Application::Get()), m_camera(Camera::Get()), m_input(Input::Get()), m_window(Application::Get().GetWindow())
    {
        m_view = m_camera.GetView();
        m_proj = glm::perspective(45.0f, (float)m_window.GetWidth()/m_window.GetHeight(), 0.1f, 100.0f);
    }

    void GameLayer::OnAttach()
    {
        glfwSetInputMode(m_window.m_GLFWwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        m_camera.SetSpeedy(10.0f);
    }


    void GameLayer::OnDetach()
    {
    }


    void GameLayer::OnUpdate()
    {

        if (m_input.KeyPress(GLFW_KEY_W))
            m_camera.Move(Movement::FORWARD, m_camera.GetSpeed() * m_app.GetDeltaTime());

        if (m_input.KeyPress(GLFW_KEY_S))
            m_camera.Move(Movement::BACKWARD, m_camera.GetSpeed() * m_app.GetDeltaTime());

        if (m_input.KeyPress(GLFW_KEY_A))
            m_camera.Move(Movement::LEFT, m_camera.GetSpeed() * m_app.GetDeltaTime());

        if (m_input.KeyPress(GLFW_KEY_D))
            m_camera.Move(Movement::RIGHT, m_camera.GetSpeed() * m_app.GetDeltaTime());

        m_view = m_camera.GetView();

        if (m_app.m_scene)
            m_app.m_scene->Render(m_view, m_proj);
    }


    void GameLayer::OnEvent(Event &e)
    {
        Dispatcher dispatcher(e);

        dispatcher.Dispatch<MouseMovedEvent>( std::bind(&GameLayer::OnMouseMoved, this, std::placeholders::_1) );
        dispatcher.Dispatch<KeyPressedEvent>( std::bind(&GameLayer::OnKeyPress, this, std::placeholders::_1) );
        dispatcher.Dispatch<WindowResizedEvent>(std::bind(&GameLayer::OnResize, this, std::placeholders::_1));
    }




    void GameLayer::OnMouseMoved(MouseMovedEvent& e)
    {
        m_camera.Update(e);
    }




    void GameLayer::OnKeyPress(KeyPressedEvent& e)
    {
        if (e.GetKeycode() == GLFW_KEY_ESCAPE && m_CursorDisabled)
        {
            glfwSetInputMode(m_window.m_GLFWwindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            m_CursorDisabled = false;
        }

        else if (e.GetKeycode() == GLFW_KEY_ESCAPE && !m_CursorDisabled)
        {
            glfwSetInputMode(m_window.m_GLFWwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            m_CursorDisabled = true;
        }

    }




    void GameLayer::OnResize(WindowResizedEvent& e)
    {
        glViewport(0, 0, e.GetX(), e.GetY());
        m_proj = glm::perspective(45.0f, (float)e.GetX() / e.GetY(), 0.1f, 100.0f);
    }
}