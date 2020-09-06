#include <pch.h>
#include "Core.h"
#include "Shader.h"
#include "Logger.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>



namespace Engine
{
    Shader::Shader(const char *v_path, const char *f_path)
        : m_vertex_path(v_path), m_fragment_path(f_path)
    {

        //Compile the vertex and the fragment shaders.
        unsigned int vertex     = this->CompileShader(GL_VERTEX_SHADER, m_vertex_path);
        unsigned int fragment   = this->CompileShader(GL_FRAGMENT_SHADER, m_fragment_path);

        //If the vertex and the fragment shaders where compiled successfully.
        if (vertex && fragment)
        {
            m_id = glCreateProgram();

            glAttachShader(m_id, vertex);
            glAttachShader(m_id, fragment);

            glLinkProgram(m_id);
            glValidateProgram(m_id);

            //----------Check For Linking Errors----------//
            int success;
            int length;

            //Get the status;
            glGetProgramiv(m_id, GL_LINK_STATUS, &success);

            //Something went wrong.
            if (!success)
            {

                //Get the info log length.
                glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);

                //Create a unique ptr to strore the message.
                std::unique_ptr<char> message = std::make_unique<char>(length);

                //Get the info log.
                glGetProgramInfoLog(m_id, length, NULL, message.get());

                //Assert it.
                ASSERT_FORMAT(0, "[ {3} && {4} ] => {5}", v_path, f_path, message.get());
            }
            //----------Check For Linking Errors----------//

        }
    }


    void Shader::Use()
    {
        glUseProgram(m_id);
    }


    void Shader::SetUniform(const char *name, int x)
    {
        glUniform1i(this->GetLocation(name), x);
    }


    void Shader::SetUniform(const char *name, float x)
    {
        glUniform1f(this->GetLocation(name), x);
    }


    void Shader::SetUniform(const char *name, glm::vec3 &vec3)
    {
        glUniform3f(this->GetLocation(name), vec3.x, vec3.y, vec3.z);
    }

    void Shader::SetUniform(const char *name, glm::mat4 &mat4)
    {
        glUniformMatrix4fv(this->GetLocation(name), 1, GL_FALSE, (const GLfloat *)&mat4[0]);
    }






    std::string Shader::ReadFile(std::string &path)
    {
        std::string full_path = std::string(RUNTIME_DIR) + path;
        std::ifstream file(full_path.c_str());

        //If the file opened successfully.
        if (file.is_open())
        {
            std::stringstream ss;

            ss << file.rdbuf();

            file.close();

            return ss.str();
        }

        ASSERT_FORMAT(0, "The file: {3} could not be opened.", full_path);
        return "";
    }


    unsigned int Shader::CompileShader(int type, std::string &path)
    {

        //Create the src string.
        std::string source  = this->ReadFile(path);
        const char *src     = source.c_str();
        
        //Create and compile the shader.
        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &src, NULL);
        glCompileShader(shader);

        //----------Check For Compilation Errors----------//
        int success;
        int length;

        //Get the status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        //Something went wrong.
        if (!success)
        {

            //Get the info log length.
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            //Create a unique ptr to strore the message.
            std::unique_ptr<char> message = std::make_unique<char>(length);

            //Get the info log.
            glGetShaderInfoLog(shader, length, NULL, message.get());

            //Assert it.
            ASSERT_FORMAT(0, "[ {3} ] => {4}", path, message.get());

            return -1;
        }
        //----------Check For Compilation Errors----------//

        return shader;
    }



    int Shader::GetLocation(const char *name)
    {

        //Bind the program;
        this->Use();

        //Get the uniform location.
        int location = glGetUniformLocation(m_id, name);

        //Assert the location.
        ASSERT_FORMAT(location != -1, "[ {3} && {4} ] => Uniform [ {5} ] does not exist!", m_vertex_path, m_fragment_path, name);

        return location;
    }
}