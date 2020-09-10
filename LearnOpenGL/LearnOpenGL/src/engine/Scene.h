#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "Graphics.h"
#include "Object.h"

namespace Engine
{

    class Scene
    {
        public:

        Scene(const std::string &name="Scene");
        virtual ~Scene();

        //Add Object to this scene.
        inline void AddObject(Object *obj) { m_objects.push_back(obj); }

        //Render Method.
        void Render(glm::mat4 &view, glm::mat4 &proj);

        //Create Object.
        Object *CreateObject(Graphics *graphics=nullptr);

        //Create Graphics.
        template<typename T>
        Graphics *CreateGraphics(const std::string &name, const std::string &path="")
        {
            //Search if the graphics object already exists.
            for (Graphics *graphics : m_graphics)
            {
                //Found.
                if (graphics->m_name == name)
                {
                    graphics->m_refCounter++;
                    return graphics;
                }
            }

            Graphics* new_graphics = new T(name, path);

            //Push the new graphics into the vector.
            this->m_graphics.push_back(new_graphics);

            //Return the new created graphics.
            return new_graphics;
        }

        private:
        std::string m_name;
        std::vector<Object *> m_objects;
        std::vector<Graphics *> m_graphics;
    };
}


#define CREATE_OBJECT(graphics_class)\
this->CreateObject( this->CreateGraphics<graphics_class>(#graphics_class) );\


#define CREATE_MODEL(graphics_class, model_path)\
this->CreateObject( this->CreateGraphics<graphics_class>(#graphics_class, model_path) );\

#endif