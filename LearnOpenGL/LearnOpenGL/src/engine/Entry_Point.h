#ifndef ENGINE_ENTRY_POINT_H
#define ENGINE_ENTRY_POINT_H


#ifdef ENGINE_ENTRY_POINT
namespace Engine
{
    Application* createApp();
}

int main(void)
{

    //Create the App object.
    Engine::Application *app = Engine::createApp();

    //Load the first scene.
    app->LoadScene(app->EntryPoint());

    //Run the APP.
    app->Run();

    //Delete the APP.
    delete app;

    //Return end terminate this process.
    return 0;
}
#endif


#endif