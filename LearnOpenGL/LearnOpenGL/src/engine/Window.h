#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H
#include <iostream>

struct GLFWwindow;

namespace Engine
{

    //Forward Declarations//
    class Application;
    class Event;
    //Forward Declarations//


    struct WindowData
    {
        friend class Application;

        std::string  m_title;
        unsigned int m_width;
        unsigned int m_height;
        void        *m_context;
        
        void (*EventCallback)(void *context, Event &e);
    };


    class Window
    {
        friend class Application;

        public:

        Window(const std::string title="LearnOpenGL", unsigned int width=800, unsigned int height=600);
        ~Window();

        void Update();

        inline unsigned int GetWidth() const {return m_WindowData.m_width;}
        inline unsigned int GetHeight() const {return m_WindowData.m_height;}
        inline std::string GetTitle() const {return m_WindowData.m_title;}

        private:

        WindowData m_WindowData;

        GLFWwindow *m_GLFWwindow;

        void BindEvents();
    };
}

#endif