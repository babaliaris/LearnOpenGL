#include "pch.h"
#include "Core.h"
#include "Application.h"
#include "Layer.h"
#include "Window.h"
#include "Events.h"

#include "Graphics/cube.h"

#include <GLFW/glfw3.h>


namespace Engine
{
    Application *Application::m_instance = nullptr;
}


Engine::Application::Application()
{

    //Store the instance in the static variable.
    ASSERT(!m_instance, "Application should have only one instance!");
    m_instance = this;

    //Initialize the Logger.
    Logger::Init();

    //Create the window.
    m_window = new Window();


    //Set Event Callback.
    m_window->m_WindowData.m_context     = (void *)this;
    m_window->m_WindowData.EventCallback = HelperEventCallback;

    //Set User Pointer.
    glfwSetWindowUserPointer( m_window->m_GLFWwindow, (void *) (&m_window->m_WindowData) );
}


Engine::Application::~Application()
{

    //Delete all the layers.
    for (Layer *layer : m_layers)
        delete layer;
}


void Engine::Application::Run()
{

    glm::mat4 proj = glm::perspective(45.0f, (float)m_window->GetWidth() / m_window->GetHeight(), 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(1.0f);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
    
    Cube cube;

    glClearColor(0,0,0,1);
    while (m_running)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        /*
        //Run all the enabled layers.
        for (Layer *layer : m_layers)
        {
            if (!layer->m_disabled)
                layer->OnUpdate();
        }
        */

       cube.Render(model, view, proj);

        m_window->Update();
    }
}




const Engine::Window& Engine::Application::GetWindow() const
{
    return *m_window;
}



void Engine::Application::PushLayer(Layer *layer)
{
    m_layers.push_back(layer);

    layer->OnAttach();
}



void Engine::Application::EventsCallback(Event &e)
{

    //Window X button pressed.
    if (e.GetType() == EventType::windowClosedEvent)
        m_running = false;

    //Forward all the events to the enabled layers.
    for (int i = m_layers.size() - 1; i >=0; i--)
    {
        if (!m_layers[i]->m_disabled)
            m_layers[i]->OnEvent(e);
    }
}



void Engine::HelperEventCallback(void *context, Engine::Event &e)
{
    ((Application *)context)->EventsCallback(e);
}