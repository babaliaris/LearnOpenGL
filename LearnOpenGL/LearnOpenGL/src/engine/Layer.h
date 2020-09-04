#ifndef ENGINE_LAYER_H
#define ENGINE_LAYER_H

namespace Engine
{
    class Layer
    {
        public:
        
        Layer();
        virtual ~Layer();

        virtual void OnAttach();
        virtual void OnDetach();
        virtual void OnUpdate();
    };
}

#endif