#include "Application.h"
#include "pch.h"
#include "Layer.h"
#include "Logger.h"
#include "Window.h"
#include "Events.h"

#include <GLFW/glfw3.h>


Engine::Application::Application()
{

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
    glClearColor(0,1,0,1);
    while (m_running)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        for (Layer *layer : m_layers)
            layer->OnUpdate();

        m_window->Update();
    }
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

    //Forward all the events to the layers.
    for (int i = m_layers.size() - 1; i >=0; i--)
        m_layers[i]->OnEvent(e);
}



void Engine::HelperEventCallback(void *context, Engine::Event &e)
{
    ((Application *)context)->EventsCallback(e);
}