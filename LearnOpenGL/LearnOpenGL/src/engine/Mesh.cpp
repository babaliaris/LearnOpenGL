#include <pch.h>
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include <glad/glad.h>

Engine::Mesh::Mesh(std::vector<Vertex *> &vertices, std::vector<unsigned int> &indices, std::vector<Texture *> &textures)
    : m_vao(0), m_vbo(0), m_ebo(0), m_indices(indices.size()), m_vertices(vertices.size()), m_textures(textures)
{

    //Generate the buffers.
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    //Bind the vertex array.
    glBindVertexArray(m_vao);

    //Upload the VBO data to the GPU.
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), (const void *)&vertices[0], GL_STATIC_DRAW);

    //Positions.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    //Normals.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, normals));
    glEnableVertexAttribArray(1);


    //Texture Coordinates.
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, textCoords));
    glEnableVertexAttribArray(2);

    //Generate and Upload the VBO data to the GPU.
    if (indices.size() > 0)
    {
        glGenBuffers(1, &m_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), (const void *)&indices[0], GL_STATIC_DRAW);
    }

    //Unbind everything.
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}




Engine::Mesh::Mesh(std::vector<float> &vertices, std::vector<Texture *> &textures)
    : m_vao(0), m_vbo(0), m_ebo(0), m_indices(0), m_vertices(vertices.size() / 8), m_textures(textures)
{
    //Generate the buffers.
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    //Bind the vertex array.
    glBindVertexArray(m_vao);

    //Upload the VBO data to the GPU.
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), (const void *)&vertices[0], GL_STATIC_DRAW);

    //Positions.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)0);
    glEnableVertexAttribArray(0);

    //Normals.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);


    //Texture Coordinates.
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);


    //Unbind everything.
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}




Engine::Mesh::~Mesh()
{

    //Delete all the textures.
    for (Texture *texture : m_textures)
        delete texture;

    //Unbind everything.
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Delete the buffers.
    glDeleteBuffers(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    if (m_ebo) glDeleteBuffers(1, &m_ebo);
}




void Engine::Mesh::Render(Shader &shader, glm::mat4 &model, glm::mat4 &view, glm::mat4 &proj)
{

    //Bind VAO and Shader.
    glBindVertexArray(m_vao);
    shader.Use();

    //Set the MVP matrices.
    shader.SetUniform("model", model);
    shader.SetUniform("view", view);
    shader.SetUniform("proj", proj);

    //Bind all the textures.
    for (int i = 0; i < m_textures.size(); i++)
    {
        shader.SetUniform(m_textures[i]->GetUniformName().c_str(), i);
        m_textures[i]->Bind(i);
    }

    //Draw Eelements.
    if (m_ebo)
        glDrawElements(GL_TRIANGLES, m_indices, GL_UNSIGNED_INT, (const void *)0);

    //Draw Arrays.
    else
        glDrawArrays(GL_TRIANGLES, 0, m_vertices);
}