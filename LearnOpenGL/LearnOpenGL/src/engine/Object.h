#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

namespace Engine
{
    class Graphics;
    class Component;
    class Scene;

    struct Transform
    {
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        Transform()
            : position(glm::vec3(0,0,0)), rotation(glm::vec3(0,0,0)), scale(glm::vec3(1,1,1))
        {
        }

        Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
            : position(pos), rotation(rot), scale(scale)
        {
        }
    };

    class Object
    {
        friend class Scene;

        public:
        Transform transform;
        std::string tag;

        //Constructor.
        Object(Graphics *graphics = nullptr);
        ~Object();

        //Render Method.
        void Render(glm::mat4 &view, glm::mat4 &proj);

        //Add Component.
        void AddComponent(Component *comp);



        private:
        Graphics *m_graphics;
        std::vector<Component *> m_components;
    };
}

#endif