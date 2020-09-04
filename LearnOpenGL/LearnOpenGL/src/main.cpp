#include <iostream>
#define ENGINE_ENTRY_POINT
#include "Engine.h"


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
        if (e.GetType() == Engine::EventType::mouseMoved)
        {
            Engine::MouseMovedEvent &event= *(Engine::MouseMovedEvent *)&e;
            LOG_ERROR("{0} , {1}", event.GetX(), event.GetY());
        }
    }
};


class LearnOpenGL : public Engine::Application
{
    public:
    
    LearnOpenGL()
    {
        PushLayer(new MyLayer());
    }


    ~LearnOpenGL()
    {

    }
};


Engine::Application *Engine::createApp()
{
    return new LearnOpenGL();
}






    /*
    GLFWwindow* window;

    
    if (!glfwInit())
        return -1;

    
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    
    glfwMakeContextCurrent(window);

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!status)
    {
        std::cout << "GLAD failed to initialize" << std::endl;
        glfwTerminate();
        return -1;
    }

    else
    {
        std::cout << "All GOOD" << std::endl;
    }



    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);


        glfwSwapBuffers(window);


        glfwPollEvents();
    }

    glfwTerminate();
    */
