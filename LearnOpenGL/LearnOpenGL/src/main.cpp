#include "pch.h"
#define ENGINE_ENTRY_POINT
#include "Engine.h"
#include <iostream>

#include "client/Scenes/EmptyScene.h"

#include "client/Layers/StencilLayer.h"
#include "client/Layers/PostProcess.h"
#include "client/Layers/CubemapLayer.h"
#include "client/Layers/ReflectionLayer.h"
#include "client/Layers/AdvancedBuffersLayer.h"


class LearnOpenGL : public Engine::Application
{
    public:
    
    LearnOpenGL()
    {
        //PushLayer(new StencilLayer());
        //PushLayer(new PostProcessLayer());
        //PushLayer(new CubemapLayer());
        //PushLayer(new ReflectionLayer());
        PushLayer(new AdvancedBuffersLayer());
    }


    ~LearnOpenGL()
    {

    }


    Engine::Scene *EntryPoint() const override
    {
        return new Engine::EmptyScene();
    }
};


Engine::Application *Engine::createApp()
{
    return new LearnOpenGL();
}