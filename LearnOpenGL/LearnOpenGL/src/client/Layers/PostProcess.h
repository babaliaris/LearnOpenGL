#pragma once
#include "Engine.h"

class PostProcessLayer : public Engine::Layer
{
public:

    ~PostProcessLayer()
    {
    }

    void OnAttach() override
    {
        //Get App, Camera and the Window.
        m_app = &Engine::Application::Get();
        m_camera = &Engine::Camera::Get();
        m_window = &m_app->GetWindow();

        //Create The Graphics To Be Rendered!!!
        m_cube = new Engine::CubeSimple("CubeSimple", "");
        m_border = new Engine::CubeBorder("CubeBorder", "");

        //Create and bind the framebuffer.
        glGenFramebuffers(1, &m_framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

        //Create and bind the depth - stencil render buffer.
        glGenRenderbuffers(1, &m_depthStencilRenderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, m_depthStencilRenderBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_window->GetWidth(), m_window->GetHeight());

        //aTTACH THE RENDERBUFFER AND UNBIND IT.
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilRenderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        //Create and bind the color texture and then allocate memory.
        glGenTextures(1, &m_colorTexture);
        glBindTexture(GL_TEXTURE_2D, m_colorTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_window->GetWidth(), m_window->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        //Attach the color texture and unbind it.
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorTexture, 0);
        glBindTexture(GL_TEXTURE_2D, 0);

        //Checkframbuffer status and unbind it.
        ASSERT( glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE , "FRAMEBUFFER ERROR!");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        //Create the post process shader.
        m_shader = m_app->CreateShader("src/client/Shaders/PostProcess.vert", "src/client/Shaders/PostProcess.frag");


        float vertices[] =
        {
            -1.0f,  1.0f, 0.0f, 1.0f, //Upper Left.   0
            -1.0f, -1.0f, 0.0f, 0.0f, //Bottom Left.  1
             1.0f, -1.0f, 1.0f, 0.0f, //Bottom right. 2
             1.0f,  1.0f, 1.0f, 1.0f, //Upper Right.  3
        };

        unsigned int indices[] =
        {
            0, 1, 2,
            3, 0, 2
        };

        glGenVertexArrays(1, &m_quad);
        glBindVertexArray(m_quad);

        unsigned int vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        unsigned int ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void *) (sizeof(float) * 2));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    }

    void OnUpdate() override
    {
        //Create the Projection (Perspective) Matrix.
        m_proj = glm::perspective(glm::radians(45.0f), (float)m_window->GetWidth() / m_window->GetHeight(), 0.1f, 100.0f);

        //Resize the Stencil and Depth RenderBuffer.
        glBindRenderbuffer(GL_RENDERBUFFER, m_depthStencilRenderBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_window->GetWidth(), m_window->GetHeight());
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        //Resize the Color Texture of the framebuffer.
        glBindTexture(GL_TEXTURE_2D, m_colorTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_window->GetWidth(), m_window->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);

        glEnable(GL_DEPTH_TEST);
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);

        glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilMask(0xFF);
        m_cube->Render(glm::mat4(1.0f), m_camera->GetView(), m_proj);

        glStencilMask(0x00);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        //glDisable(GL_DEPTH_TEST);
        glm::mat4 border_model = glm::scale(glm::mat4(1.0f), glm::vec3(1.1f, 1.1f, 1.1f));
        m_border->Render(border_model, m_camera->GetView(), m_proj);

        

        //Bind the framebuffer and the post process shader.
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_colorTexture);
        m_shader->Use();
        m_shader->SetUniform("u_Framebuffer", 0);
        glBindVertexArray(m_quad);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        



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

    //Scene spesific stuff goes here!
    Engine::CubeSimple* m_cube;
    Engine::CubeBorder* m_border;

    Engine::Shader* m_shader;

    unsigned int m_quad;
    unsigned int m_framebuffer;
    unsigned int m_colorTexture;
    unsigned int m_depthStencilRenderBuffer;




};

