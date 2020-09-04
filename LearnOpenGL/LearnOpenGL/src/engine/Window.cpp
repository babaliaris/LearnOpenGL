#include "pch.h"
#include "Window.h"
#include "Logger.h"
#include "Core.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine
{
    Window::Window(const std::string title, unsigned int width, unsigned int height)
        : m_title(title), m_width(width), m_height(height)
    {

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
        
    }

    Window::~Window()
    {

    }


    void Window::Update()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_GLFWwindow);
    }


}