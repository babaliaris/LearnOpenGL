#include "pch.h"
#include "Component.h"

namespace Engine
{
    Component::Component()
        : core(&Application::Get())
    {
    }


    void Component::OnStart()
    {
    }


    void Component::OnUpdate()
    {
    }
}