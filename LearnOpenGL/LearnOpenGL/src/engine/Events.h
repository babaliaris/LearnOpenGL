#ifndef ENGINE_EVENTS_H
#define ENGINE_EVENTS_H
#include <functional>

namespace Engine
{

    enum class EventType
    {
        None=0,
        keyPress, keyRelease, keyRepeat,
        windowClosedEvent, windowResized,
        mouseMoved, mousePressed, mouseReleased, mouseScrolled
    };



    class Event
    {

        //Public Members.
        public:
        inline EventType GetType() const {return m_type;}

        protected:
        EventType m_type;
    };




    class KeyPressedEvent : public Event
    {
        public:

        //Static get type.
        inline static EventType GetStaticType() {return EventType::keyPress;}

        //Constructor.
        KeyPressedEvent(int key)
            : m_keycode(key)
        {
            m_type = EventType::keyPress;
        }

        //Get Methods.
        inline int GetKeycode() const {return m_keycode;}


        //Private Members.
        private:
        int m_keycode;

    };





    class KeyRepeatEvent : public Event
    {
        public:

        //Static get type.
        inline static EventType GetStaticType() {return EventType::keyRepeat;}

        //Constructor.
        KeyRepeatEvent(int key)
            : m_keycode(key)
        {
            m_type = EventType::keyRepeat;
        }

        //Get Methods.
        inline int GetKeycode() const {return m_keycode;}


        //Private Members.
        private:
        int m_keycode;

    };





    class KeyReleasedEvent : public Event
    {
        public:

        //Static get type.
        inline static EventType GetStaticType() {return EventType::keyRelease;}

        //Constructor.
        KeyReleasedEvent(int key)
            : m_keycode(key)
        {
            m_type = EventType::keyRelease;
        }

        //Get Methods.
        inline int GetKeycode() const {return m_keycode;}


        //Private Members.
        private:
        int m_keycode;

    };




    class WindowClosedEvent : public Event
    {
        public:

        //Static get type.
        inline static EventType GetStaticType() {return EventType::windowClosedEvent;}

        //Constructor.
        WindowClosedEvent()
        {
            m_type = EventType::windowClosedEvent;
        }

    };




    class WindowResizedEvent : public Event
    {
        public:

        //Static get type.
        inline static EventType GetStaticType() {return EventType::windowResized;}

        //Constructor.
        WindowResizedEvent(int x, int y)
            : m_x(x), m_y(y)
        {
            m_type = EventType::windowResized;
        }

        //Inline Methods.
        inline int GetX() const {return m_x;}
        inline int GetY() const {return m_y;}

        private:
        int m_x;
        int m_y;

    };




    class MouseMovedEvent : public Event
    {
        public:

        //Static get type.
        inline static EventType GetStaticType() {return EventType::mouseMoved;}

        //Constructor.
        MouseMovedEvent(int x, int y)
            : m_x(x), m_y(y)
        {
            m_type = EventType::mouseMoved;
        }

        //Inline Methods.
        inline int GetX() const {return m_x;}
        inline int GetY() const {return m_y;}

        private:
        int m_x;
        int m_y;

    };




    class MousePressedEvent : public Event
    {
        public:

        //Static get type.
        inline static EventType GetStaticType() {return EventType::mousePressed;}

        //Constructor.
        MousePressedEvent(int button)
            : m_button(button)
        {
            m_type = EventType::mousePressed;
        }

        //Inline Methods.
        inline int GetButton() const {return m_button;}

        private:
        int m_button;

    };



    class MouseReleasedEvent : public Event
    {
        public:

        //Static get type.
        inline static EventType GetStaticType() {return EventType::mouseReleased;}

        //Constructor.
        MouseReleasedEvent(int button)
            : m_button(button)
        {
            m_type = EventType::mouseReleased;
        }

        //Inline Methods.
        inline int GetButton() const {return m_button;}

        private:
        int m_button;

    };




    class MouseScrolledEvent : public Event
    {
        public:

        //Static get type.
        inline static EventType GetStaticType() {return EventType::mouseScrolled;}

        //Constructor.
        MouseScrolledEvent(float x, float y)
            : m_x(x), m_y(y)
        {
            m_type = EventType::mouseScrolled;
        }

        //Inline Methods.
        inline float GetX() const {return m_x;}
        inline float GetY() const {return m_y;}

        private:
        float m_x;
        float m_y;

    };




    



    class Dispatcher
    {

        //Dispatcher callback.
        template<typename T>
        using DispatchCallback = std::function<void(T&)>;



        public:

        //Constructor.
        Dispatcher(Event &e) 
            : m_event(e)
        {
        }
        
        //Dispatch.
        template<typename T>
        void Dispatch(DispatchCallback<T> callback)
        {
            //Call the callback function.
            if (m_event.GetType() == T::GetStaticType())
                callback( *(T *)&m_event );
        }


        private:
        Event &m_event;
    };
    

}

#endif