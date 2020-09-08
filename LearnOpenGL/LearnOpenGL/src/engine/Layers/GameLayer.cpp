#include "pch.h"
#include "GameLayer.h"
#include "../Application.h"
#include "../Scene.h"
#include "../Window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{

    GameLayer::GameLayer()
        : m_app(Application::Get())
    {
        m_view = glm::mat4(1.0f);
        m_view = glm::translate(m_view, glm::vec3(0.0f, 0.0f, -2.0f));

        const Window &window = m_app.GetWindow();
        m_proj = glm::perspective(45.0f, (float)window.GetWidth()/window.GetHeight(), 0.1f, 100.0f);
    }

    void GameLayer::OnAttach()
    {

    }


    void GameLayer::OnDetach()
    {

    }


    void GameLayer::OnUpdate()
    {
        if (m_app.m_scene)
            m_app.m_scene->Render(m_view, m_proj);
    }


    void GameLayer::OnEvent(Event &e)
    {

    }
}