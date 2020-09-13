#include "pch.h"
#include "Object.h"
#include "Graphics.h"
#include "Component.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
    Object::Object(Graphics *graphics)
        : m_graphics(graphics)
    {
    }




    Object::~Object()
    {   
        //Delete all the components.
        for (Component *cmp : m_components)
            delete cmp;
    }




    void Object::Render(glm::mat4 &view, glm::mat4 &proj)
    {

        //Create the model.
        glm::mat4 model = glm::mat4(1.0f);

        //Translate.
        model = glm::translate(model, this->transform.position);
        
        //Rotate at x, y, z .
        model = glm::rotate(model, glm::radians(this->transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(this->transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(this->transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        //Scale.
        model = glm::scale(model, this->transform.scale);


        //Run all the Components.
        for (Component *cmp : m_components)
        {   
            //Call the onStart method.
            if (cmp->m_onStart)
            {
                cmp->OnStart();
                cmp->m_onStart = false;
            }

            //Call Update.
            else
                cmp->OnUpdate();
        }

        //Render the graphics.
        if (this->m_graphics)
            this->m_graphics->Render(model, view, proj);
    }



    void Object::AddComponent(Component *cmp)
    {
        cmp->self = this;
        this->m_components.push_back(cmp);
    }




    Shader* Object::GetShader()
    {
        return m_graphics->m_shader;
    }
}