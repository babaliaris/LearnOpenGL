#include "pch.h"
#define ENGINE_ENTRY_POINT
#include "Engine.h"
#include <iostream>

#include "client/Scenes/TestScene.h"


class MyLayer : public Engine::Layer
{
    public:

    MyLayer()
    {

    }

    ~MyLayer()
    {

    }

    void OnAttach() override
    {

    }

    void OnUpdate() override
    {
    }

    
    void OnEvent(Engine::Event &e)
    {
        Engine::Dispatcher dispatcher(e);


        dispatcher.Dispatch<Engine::WindowResizedEvent>( std::bind(&MyLayer::OnResize, this, std::placeholders::_1) );

    }

    void OnResize(Engine::WindowResizedEvent &e)
    {
        LOG_INFO("{0} , {1}", e.GetX(), e.GetY());
    }
};


class LearnOpenGL : public Engine::Application
{
    public:
    
    LearnOpenGL()
    {
        Engine::Layer *layer = new MyLayer();
        PushLayer(layer);
    }


    ~LearnOpenGL()
    {

    }


    Engine::Scene *EntryPoint() const override
    {
        return new Engine::TestScene();
    }
};


Engine::Application *Engine::createApp()
{
    return new LearnOpenGL();
}