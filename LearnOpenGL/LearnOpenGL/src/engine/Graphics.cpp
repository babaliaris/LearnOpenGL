#include "pch.h"
#include "Graphics.h"
#include "Application.h"

namespace Engine
{
    Graphics::Graphics(const char *name, const char*path, const char *vert_path, const char *frag_path)
        : m_name(name), m_shader(Application::Get().CreateShader(vert_path, frag_path))
    {
    }



    Graphics::~Graphics()
    {
        LOG_INFO("[Graphics: {0}] => Deleted!", this->m_name);

        for (Mesh *mesh : m_meshes)
            delete mesh;

        m_shader->m_RefCounter--;

        if (m_shader->m_RefCounter == 0)
            delete m_shader;
    }


    void Graphics::Render(glm::mat4 &model, glm::mat4 &view, glm::mat4 &proj)
    {
        
        //Shader should be initialized at this point.
        ASSERT_FORMAT(m_shader, "[ Graphics: {3} ] => The shader has not been initialized.", m_name);

        //Render all the meshes.
        for (Mesh *mesh : m_meshes)
            mesh->Render(*m_shader, model, view, proj);
    }
}