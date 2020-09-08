#include "pch.h"
#include "Core.h"
#include "Texture.h"
#include "Application.h"
#include <stb_image.h>
#include <glad/glad.h>

namespace Engine
{
    Texture::Texture(const char *path, const char *uniform_name, bool flip)
        : m_id(0), m_countRef(1), m_path(path), m_uniform_name(uniform_name)
    {

        //Flipt the image vertically.
        stbi_set_flip_vertically_on_load(flip);
        
        //Create the full
        std::string full_path = std::string(RUNTIME_DIR) + path;

        //Load the image into the memory.
        unsigned char *data = stbi_load(full_path.c_str(), &m_width, &m_height, &m_channels, 0);
        ASSERT_FORMAT(data, "[Texture: {3}] Could not be opened => {4}", path, stbi_failure_reason());

        //If the read was successfull.
        if (data)
        {

            //Generate and bind the Texture.
            glGenTextures(1, &m_id);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_id);

            //Set Wraps and Filters.
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

            //-----Get the right GL_* channel enum value-----//
            int channel;
            switch (m_channels)
            {
                case 1:
                    channel = GL_R;
                    break;

                case 2:
                    channel = GL_RG;
                    break;

                case 3:
                    channel = GL_RGB;
                    break;

                case 4:
                    channel = GL_RGBA;
                    break;
                
                default:
                    break;
            }
            //-----Get the right GL_* channel enum value-----//


            //Upload the texture to the GPU.
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, channel, GL_UNSIGNED_BYTE, (const void *)data);

            //Generate Mimpaps.
            glGenerateMipmap(GL_TEXTURE_2D);

            //Free the memory of the pixels.
            stbi_image_free(data);

            //Unbind the Texture.
            glBindTexture(GL_TEXTURE_2D, 0);

            LOG_INFO("[Texture: {0}] => Created!", this->m_path);
        }
    }


    Texture::~Texture()
    {
        LOG_INFO("[Texture: {0}] => Deleted!", this->m_path);

        this->Unbind();
        glDeleteTextures(1, &m_id);
    }



    void Texture::Bind(int unit)
    {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }


    void Texture::Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}