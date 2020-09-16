#pragma once
#include "Engine.h"

class CubemapLayer : public Engine::Layer
{
public:

    CubemapLayer()
    {
        m_vertices = {

            // positions
            -1.0f, -1.0f, -1.0f, 
            1.0f, -1.0f, -1.0f,  
            1.0f,  1.0f, -1.0f,  
            1.0f,  1.0f, -1.0f,  
            -1.0f,  1.0f, -1.0f, 
            -1.0f, -1.0f, -1.0f, 

            -1.0f, -1.0f,  1.0f, 
            1.0f, -1.0f,  1.0f,  
            1.0f,  1.0f,  1.0f,  
            1.0f,  1.0f,  1.0f,  
            -1.0f,  1.0f,  1.0f, 
            -1.0f, -1.0f,  1.0f, 

            -1.0f,  1.0f,  1.0f, 
            -1.0f,  1.0f, -1.0f, 
            -1.0f, -1.0f, -1.0f, 
            -1.0f, -1.0f, -1.0f, 
            -1.0f, -1.0f,  1.0f, 
            -1.0f,  1.0f,  1.0f, 

            1.0f,  1.0f,  1.0f,  
            1.0f,  1.0f, -1.0f,  
            1.0f, -1.0f, -1.0f,  
            1.0f, -1.0f, -1.0f,  
            1.0f, -1.0f,  1.0f,  
            1.0f,  1.0f,  1.0f,  

            -1.0f, -1.0f, -1.0f, 
            1.0f, -1.0f, -1.0f,  
            1.0f, -1.0f,  1.0f,  
            1.0f, -1.0f,  1.0f,  
            -1.0f, -1.0f,  1.0f, 
            -1.0f, -1.0f, -1.0f, 

            -1.0f,  1.0f, -1.0f, 
            1.0f,  1.0f, -1.0f,  
            1.0f,  1.0f,  1.0f,  
            1.0f,  1.0f,  1.0f,  
            -1.0f,  1.0f,  1.0f, 
            -1.0f,  1.0f, -1.0f
        };
    }

    void OnAttach() override
    {
        //Get App, Camera and the Window.
        m_app = &Engine::Application::Get();
        m_camera = &Engine::Camera::Get();
        m_window = &m_app->GetWindow();

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        unsigned int vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        m_shader = m_app->CreateShader("src/client/Shaders/Cubemap.vert", "src/client/Shaders/Cubemap.frag");

        glGenTextures(1, &m_cubemap);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemap);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        std::vector<std::string> faces = { "right.jpg","left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg" };

        for (int i = 0; i < faces.size(); i++)
        {
            int width, height, channels;

            std::string full_path = RUNTIME_DIR + std::string("Assets/cubemaps/skybox/") + faces[i];
            unsigned char* data = stbi_load(full_path.c_str(), &width, &height, &channels, 0);

            ASSERT(data, "Image could not be opened!");

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

            stbi_image_free(data);
        }

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void OnUpdate() override
    {
        //Create the Projection (Perspective) Matrix.
        m_proj = glm::perspective(glm::radians(45.0f), (float)m_window->GetWidth() / m_window->GetHeight(), 0.1f, 100.0f);

        glDisable(GL_DEPTH_TEST);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemap);
        m_shader->Use();
        m_shader->SetUniform("view", m_camera->GetView());
        m_shader->SetUniform("proj", m_proj);
        m_shader->SetUniform("u_Sampler", 0);
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glEnable(GL_DEPTH_TEST);
    }


    void OnEvent(Engine::Event& e)
    {
    }


private:

    //This needs to be in every single layer!!!
    Engine::Application* m_app;
    Engine::Camera* m_camera;
    const Engine::Window* m_window;
    glm::mat4 m_proj;

    std::vector<float> m_vertices;

    unsigned int m_vao, m_cubemap;
    Engine::Shader* m_shader;
};