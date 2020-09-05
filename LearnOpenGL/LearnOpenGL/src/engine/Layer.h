#ifndef ENGINE_LAYER_H
#define ENGINE_LAYER_H

namespace Engine
{
    class Event;
    class Application;

    class Layer
    {
        friend class Application;

        public:
        
        Layer();
        virtual ~Layer();

        virtual void OnAttach();
        virtual void OnDetach();
        virtual void OnUpdate();
        virtual void OnEvent(Event &e);

        inline void setDisable(bool value){ m_disabled=value; }


        private:
        bool m_disabled = false;
    };
}

#endif