#pragma once
#include "Engine.h"

class AdvancedBuffersLayer : public Engine::Layer
{
public:

    AdvancedBuffersLayer()
    {



        m_positions = {

            // positions         
            -0.5f, -0.5f, -0.5f, 
            0.5f, -0.5f, -0.5f,  
            0.5f,  0.5f, -0.5f,  
            0.5f,  0.5f, -0.5f,  
            -0.5f,  0.5f, -0.5f, 
            -0.5f, -0.5f, -0.5f, 

            -0.5f, -0.5f,  0.5f, 
            0.5f, -0.5f,  0.5f,  
            0.5f,  0.5f,  0.5f,  
            0.5f,  0.5f,  0.5f,  
            -0.5f,  0.5f,  0.5f, 
            -0.5f, -0.5f,  0.5f, 

            -0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f, -0.5f, 
            -0.5f, -0.5f, -0.5f, 
            -0.5f, -0.5f, -0.5f, 
            -0.5f, -0.5f,  0.5f, 
            -0.5f,  0.5f,  0.5f, 

            0.5f,  0.5f,  0.5f,  
            0.5f,  0.5f, -0.5f,  
            0.5f, -0.5f, -0.5f,  
            0.5f, -0.5f, -0.5f,  
            0.5f, -0.5f,  0.5f,  
            0.5f,  0.5f,  0.5f,  

            -0.5f, -0.5f, -0.5f, 
            0.5f, -0.5f, -0.5f,  
            0.5f, -0.5f,  0.5f,  
            0.5f, -0.5f,  0.5f,  
            -0.5f, -0.5f,  0.5f, 
            -0.5f, -0.5f, -0.5f, 

            -0.5f,  0.5f, -0.5f, 
            0.5f,  0.5f, -0.5f,  
            0.5f,  0.5f,  0.5f,  
            0.5f,  0.5f,  0.5f,  
            -0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f, -0.5f 
        };



        m_normals = {

             // normals          
             0.0f,  0.0f, -1.0f, 
            0.0f,  0.0f, -1.0f,  
            0.0f,  0.0f, -1.0f,  
            0.0f,  0.0f, -1.0f,  
             0.0f,  0.0f, -1.0f, 
             0.0f,  0.0f, -1.0f, 

             0.0f,  0.0f, 1.0f,  
            0.0f,  0.0f, 1.0f,   
            0.0f,  0.0f, 1.0f,   
            0.0f,  0.0f, 1.0f,   
             0.0f,  0.0f, 1.0f,  
             0.0f,  0.0f, 1.0f,  

            -1.0f,  0.0f,  0.0f, 
            -1.0f,  0.0f,  0.0f, 
            -1.0f,  0.0f,  0.0f, 
            -1.0f,  0.0f,  0.0f, 
            -1.0f,  0.0f,  0.0f, 
            -1.0f,  0.0f,  0.0f, 

            1.0f,  0.0f,  0.0f,  
            1.0f,  0.0f,  0.0f,  
            1.0f,  0.0f,  0.0f,  
            1.0f,  0.0f,  0.0f,  
            1.0f,  0.0f,  0.0f,  
            1.0f,  0.0f,  0.0f,  

             0.0f, -1.0f,  0.0f, 
            0.0f, -1.0f,  0.0f,  
            0.0f, -1.0f,  0.0f,  
            0.0f, -1.0f,  0.0f,  
             0.0f, -1.0f,  0.0f, 
             0.0f, -1.0f,  0.0f, 

             0.0f,  1.0f,  0.0f, 
            0.0f,  1.0f,  0.0f,  
            0.0f,  1.0f,  0.0f,  
            0.0f,  1.0f,  0.0f,  
             0.0f,  1.0f,  0.0f, 
             0.0f,  1.0f,  0.0f
        };


        m_coordinates = {

             // texture coords
             0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
             0.0f, 1.0f,
             0.0f, 0.0f,

             0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
             0.0f, 1.0f,
             0.0f, 0.0f,

             1.0f, 0.0f,
             1.0f, 1.0f,
             0.0f, 1.0f,
             0.0f, 1.0f,
             0.0f, 0.0f,
             1.0f, 0.0f,

            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,

             0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 0.0f,
             0.0f, 0.0f,
             0.0f, 1.0f,

             0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 0.0f,
             0.0f, 0.0f,
             0.0f, 1.0f
        };
    }

    void OnAttach() override
    {
        //Get App, Camera and the Window.
        m_app = &Engine::Application::Get();
        m_camera = &Engine::Camera::Get();
        m_window = &m_app->GetWindow();


        glGenVertexArrays(1, &m_cube);
        glBindVertexArray(m_cube);

        unsigned int vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (m_positions.size() + m_normals.size() + m_coordinates.size()), NULL, GL_STATIC_DRAW);

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * m_positions.size(), &m_positions[0]);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * m_positions.size(), sizeof(float) * m_normals.size(), &m_normals[0]);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * (m_positions.size() + m_normals.size()), sizeof(float) * m_coordinates.size(), &m_coordinates[0]);



        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
        glEnableVertexAttribArray(0);


        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void*)(sizeof(float) * m_positions.size()));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)(sizeof(float) * (m_positions.size() + m_normals.size())));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



        m_cubeShader = m_app->CreateShader("src/engine/Shaders/Basic.vert", "src/engine/Shaders/Basic.frag");

        m_diffuse  = m_app->CreateTexture("Assets/container2.png", "diffuse");
        m_specular = m_app->CreateTexture("Assets/specular.png", "specular");
    }

    void OnUpdate() override
    {
        //Create the Projection (Perspective) Matrix.
        m_proj = glm::perspective(glm::radians(45.0f), (float)m_window->GetWidth() / m_window->GetHeight(), 0.1f, 100.0f);


        m_diffuse->Bind(0);
        m_diffuse->Bind(1);
        m_cubeShader->Use();
        m_cubeShader->SetUniform("model", glm::mat4(1.0f));
        m_cubeShader->SetUniform("view", m_camera->GetView());
        m_cubeShader->SetUniform("proj", m_proj);
        m_cubeShader->SetUniform("diffuse", 0);
        m_cubeShader->SetUniform("specular", 1);
        glBindVertexArray(m_cube);
        glDrawArrays(GL_TRIANGLES, 0, 36);

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

    std::vector<float> m_positions, m_normals, m_coordinates;

    unsigned int m_cube;
    Engine::Shader* m_cubeShader;

    Engine::Texture* m_diffuse, * m_specular;
};
