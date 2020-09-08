#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H
#include "Application.h"
#include "Object.h"
#include "Core.h"

namespace Engine
{
    class Object;

    class Component
    {
        friend class Object;

        public:
        Application *core;
        Object *self;


        Component();

        virtual void OnStart();
        virtual void OnUpdate();

        private:
        bool m_onStart = true;
    };
}

#endif