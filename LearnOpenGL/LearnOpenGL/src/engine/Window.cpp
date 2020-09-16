#include "pch.h"
#include "Window.h"
#include "Logger.h"
#include "Core.h"
#include "Events.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine
{
    Window::Window(const std::string title, unsigned int width, unsigned int height)
    {
        
        //Initialize Window Data.
        m_WindowData.m_title  = title;
        m_WindowData.m_width  = width;
        m_WindowData.m_height = height;

        //Initialize GLFW.
        int status = glfwInit();
        ASSERT(status, "GLFW Failed to initialize");

        //OpenGL Version 3.3.0 Core Profile.
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        //Create the window.
        m_GLFWwindow = glfwCreateWindow((int)width, (int)height, title.c_str(), NULL, NULL);
        ASSERT(m_GLFWwindow, "GLFW Failed to create the Window.");

        //Make the OpenGL Context.
        glfwMakeContextCurrent(m_GLFWwindow);

        //Initialize GLAD.
        status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        ASSERT(status, "GLAD Failed to initialize.");

        //Initialize the ViewPort.
        glViewport(0, 0, width, height);

        //Enable Depth Test.
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_STENCIL_TEST);

        //Bind Events.
        this->BindEvents();
        
    }

    Window::~Window()
    {

    }


    void Window::Update()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_GLFWwindow);
    }




    void Window::BindEvents()
    {


        //Bind Key Events.
        glfwSetKeyCallback(m_GLFWwindow, [](GLFWwindow *window, int key, int scan, int action, int mods)
        {
            WindowData *data = (WindowData *)glfwGetWindowUserPointer(window);

            switch (action)
            {

                case GLFW_PRESS:
                {
                    KeyPressedEvent e(key);
                    data->EventCallback(data->m_context, e);
                    break;
                }


                case GLFW_RELEASE:
                {
                    KeyReleasedEvent e(key);
                    data->EventCallback(data->m_context, e);
                    break;
                }


                case GLFW_REPEAT:
                {
                    KeyRepeatEvent e(key);
                    data->EventCallback(data->m_context, e);
                    break;
                }
                
                default:
                    break;
            }
        });




        glfwSetWindowCloseCallback(m_GLFWwindow, [](GLFWwindow *window)
        {
            WindowData *data = (WindowData *)glfwGetWindowUserPointer(window);

            WindowClosedEvent e;

            data->EventCallback(data->m_context, e);
        });



        glfwSetCursorPosCallback(m_GLFWwindow, [](GLFWwindow *window, double x, double y)
        {
            WindowData *data = (WindowData *)glfwGetWindowUserPointer(window);

            MouseMovedEvent e((float)x, (float)y);

            data->EventCallback(data->m_context, e);
        });


        glfwSetMouseButtonCallback(m_GLFWwindow, [](GLFWwindow *window, int button, int action, int mods)
        {
            WindowData *data = (WindowData *)glfwGetWindowUserPointer(window);

            switch (action)
            {

                case GLFW_PRESS:
                {
                    MousePressedEvent e(button);
                    data->EventCallback(data->m_context, e);
                    break;
                }


                case GLFW_RELEASE:
                {
                    MouseReleasedEvent e(button);
                    data->EventCallback(data->m_context, e);
                    break;
                }
                
                default:
                    break;
            }
        });


        glfwSetScrollCallback(m_GLFWwindow, [](GLFWwindow *window, double x, double y)
        {
            WindowData *data = (WindowData *)glfwGetWindowUserPointer(window);

            MouseScrolledEvent e((float)x, (float)y);

            data->EventCallback(data->m_context, e);
        });


        glfwSetWindowSizeCallback(m_GLFWwindow, [](GLFWwindow *window, int x, int y)
        {
            WindowData *data = (WindowData *)glfwGetWindowUserPointer(window);

            WindowResizedEvent e(x, y);

            data->EventCallback(data->m_context, e);
        });
    }


}