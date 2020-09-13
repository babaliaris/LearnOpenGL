#ifndef ENGINE_GRAPHICS_H
#define ENGINE_GRAPHICS_H
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "Mesh.h"
#include "Shader.h"
#include "Core.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Application.h"
#include "Window.h"

namespace Engine
{

    class Scene;

    class Graphics
    {
        friend class Scene;
        friend class Object;

        public:
        std::vector<Texture *> __engine_graphics_creator_textures__;

        //Constructors-Deconstructor.
        Graphics(const char *name, const char *path, const char *vert_path, const char *frag_path);
        virtual ~Graphics();

        //Render.
        void Render(glm::mat4 &model, glm::mat4 &view, glm::mat4 &proj);

        //Add Mesh.
        inline void AddMesh(Mesh *mesh) { m_meshes.push_back(mesh); }

        //Get Name.
        inline std::string& GetName() { return m_name; }

        private:
        unsigned int m_refCounter = 1;
        std::string m_name;
        Shader *m_shader;
        std::vector<Mesh *> m_meshes;
    };
}




#define CREATE_TEXTURE(path, type){\
\
    Application &app = Application::Get();\
    Texture *texture = app.CreateTexture(path, type);\
    __engine_graphics_creator_textures__.push_back(texture);\
\
}


#define CREATE_MESH(vertices, ...){\
\
        __VA_ARGS__\
        Mesh *mesh = new Mesh(vertices, __engine_graphics_creator_textures__);\
        this->AddMesh(mesh);\
        __engine_graphics_creator_textures__.clear();\
\
}


#define CREATE_MODEL_MESH(vertices, indices, textures){\
\
        Mesh *mesh = new Mesh(vertices, indices, textures);\
        this->AddMesh(mesh);\
\
}

#endif