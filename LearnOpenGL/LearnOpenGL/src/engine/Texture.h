#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H
#include <iostream>

namespace Engine
{

    class Application;
    class Mesh;

    class Texture
    {
        friend class Application;
        friend class Mesh;

        public:
        Texture(const char *path, const char *uniform_name="diffuse", bool flip=1);
        ~Texture();

        void Bind(int unit=0);
        void Unbind();

        inline int GetWidth() { return m_width; }
        inline int GetHeight() { return m_height; }
        inline int GetChannels() { return m_channels; }
        inline std::string& GetUniformName() { return m_uniform_name; }

        private:
        unsigned int m_id, m_countRef;
        std::string m_path, m_uniform_name;
        int m_width, m_height, m_channels;

    };
}


#endif