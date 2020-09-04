#ifndef ENGINE_EVENTS_H
#define ENGINE_EVENTS_H

namespace Engine
{

    enum class EventType
    {
        None=0,
        keyPress, keyRelease, keyRepeat,
        windowClosedEvent,
        mouseMoved
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

        //Constructor.
        WindowClosedEvent()
        {
            m_type = EventType::windowClosedEvent;
        }

    };




    class MouseMovedEvent : public Event
    {
        public:

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

}

#endif