#ifndef ENGINE_ENTRY_POINT_H
#define ENGINE_ENTRY_POINT_H


#ifdef ENGINE_ENTRY_POINT
namespace Engine
{
    Application* createApp();
}

int main(void)
{
    Engine::Application *app = Engine::createApp();

    app->Run();

    delete app;

    return 0;
}
#endif


#endif