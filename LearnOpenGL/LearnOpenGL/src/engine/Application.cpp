#include "Application.h"
#include "pch.h"
#include "Layer.h"
#include "Logger.h"
#include "Window.h"

#include <GLFW/glfw3.h>



Engine::Application::Application()
    : m_layers(new std::vector<Layer*>())
{
    Logger::Init();

    m_window = new Window();
}


Engine::Application::~Application()
{

    //Delete all the layers.
    for (Layer *layer : *m_layers)
        delete layer;

    //Delete the layers vector.
    delete m_layers;
}


void Engine::Application::Run()
{
    glClearColor(0,1,0,1);
    while (m_running)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        for (Layer *layer : *m_layers)
            layer->OnUpdate();

        m_window->Update();
    }
}


void Engine::Application::PushLayer(Layer *layer)
{
    m_layers->push_back(layer);

    layer->OnAttach();
}