#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Graphics.h"


namespace Engine
{
    Scene::Scene(const std::string &name)
        : m_name(name)
    {
    }


    Scene::~Scene()
    {

        //Delete all the game objects.
        for (Object *obj : m_objects)
            delete obj;

        //Delete all the graphics objects.
        for (Graphics *graphs : m_graphics)
            delete graphs;
    }


    void Scene::Render(glm::mat4 &view, glm::mat4 &proj)
    {

        //Render all the game objects.
        for (int i = 0; i < m_objects.size(); i++)
        {
            this->m_objects[i]->Render(view, proj);
        }
    }


    Engine::Object *Scene::CreateObject(Graphics *graphics)
    {
        Object *obj = new Object(graphics);
        this->AddObject(obj);
        return obj;
    }

    Object* Scene::CreateDirectionalLight(Graphics* graphics)
    {
        Object* obj = new DirectionalLight(graphics);
        this->AddObject(obj);
        return obj;
    }

    Object* Scene::CreatePointLight(Graphics* graphics)
    {
        Object* obj = new PointLight(graphics);
        this->AddObject(obj);
        return obj;
    }

}