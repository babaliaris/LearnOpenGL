#include "pch.h"
#include "Core.h"
#include "Application.h"
#include "Layer.h"
#include "Window.h"
#include "Events.h"
#include "Texture.h"
#include "Scene.h"
#include "Layers/GameLayer.h"
#include "Input.h"
#include "Shader.h"

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

    //Push the game layer.
    this->PushLayer(new GameLayer());
}


Engine::Application::~Application()
{

    //Delete all the layers.
    for (Layer *layer : m_layers)
        delete layer;
}


void Engine::Application::Run()
{

    float current_time, prev_time = 0;

    glClearColor(0,0,0,1);
    while (m_running)
    {
        //Calculate delta time.
        current_time    = (float)glfwGetTime();
        m_deltaTime     = current_time - prev_time;
        prev_time       = current_time;


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
        
        //Run all the enabled layers.
        for (Layer *layer : m_layers)
        {
            if (!layer->m_disabled)
                layer->OnUpdate();
        }

        //Reset the scrolling variables.
        Input::s_scrollX = 0;
        Input::s_scrollY = 0;

        //Update the window.
        m_window->Update();
    }

    //Delete the scene.
    delete m_scene;
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




void Engine::Application::LoadScene(Scene* new_scene)
{
    if (m_scene)
        delete m_scene;

    m_scene = new_scene;
}




Engine::Texture* Engine::Application::CreateTexture(const std::string &path, const std::string &unifrom_name, bool flip)
{

    //Check if the texture already exists.
    for (Texture *text : m_textures)
    {
        //Found.
        if (text->m_path == path)
        {
            text->m_countRef++;
            return text;
        }
    }

    //Create a new Texture.
    Texture *texture = new Texture(path.c_str(), unifrom_name.c_str(), flip);

    //Push back the texture stuct the APP vector.
    this->m_textures.push_back(texture);

    //Return the new created Texture.
    return texture;
}





Engine::Shader* Engine::Application::CreateShader(const std::string& vert_path, const std::string& frag_path)
{
    //Check if the shader already exists.
    for (Shader* shader : m_shaders)
    {
        //Found.
        if (vert_path == shader->m_vertex_path && frag_path == shader->m_fragment_path)
        {
            shader->m_RefCounter++;
            return shader;
        }
    }

    //Create a new Shader.
    Shader* new_shader = new Shader(vert_path.c_str(), frag_path.c_str());

    //Push back the shader stuct the APP vector.
    this->m_shaders.push_back(new_shader);

    //Return the new created Texture.
    return new_shader;
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