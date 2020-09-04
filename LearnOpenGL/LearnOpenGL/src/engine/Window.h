#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H
#include <iostream>

struct GLFWwindow;

namespace Engine
{
    class Window
    {
        public:

        Window(const std::string title="LearnOpenGL", unsigned int width=800, unsigned int height=600);
        ~Window();

        void Update();

        inline unsigned int GetWidth() const {return m_width;}
        inline unsigned int GetHeight() const {return m_height;}
        inline std::string GetTitle() const {return m_title;}

        private:
        std::string  m_title;
        unsigned int m_width;
        unsigned int m_height;

        GLFWwindow *m_GLFWwindow;
    };
}

#endif