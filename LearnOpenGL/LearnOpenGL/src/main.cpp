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
