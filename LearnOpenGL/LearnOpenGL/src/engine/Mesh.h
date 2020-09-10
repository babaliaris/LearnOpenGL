#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H
#include <vector>
#include <glm/glm.hpp>

namespace Engine
{

    class Texture;
    class Shader;



    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normals;
        glm::vec2 textCoords;
    };



    class Mesh
    {
        public:
        Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture *> &textures);
        Mesh(std::vector<float> &vertices, std::vector<Texture *> &textures);
        ~Mesh();

        void Render(Shader &shader, glm::mat4 &model, glm::mat4 &view, glm::mat4 &proj);

        private:
        unsigned int m_vao, m_vbo, m_ebo;
        unsigned int m_indices, m_vertices;
        std::vector<Texture *> m_textures;
    };
}


#endif