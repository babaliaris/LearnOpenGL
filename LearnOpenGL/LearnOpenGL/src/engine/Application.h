#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H
#include <vector>


namespace Engine
{   

    //-----Forward Declarations-----//
    class Layer;
    class Window;
    class Event;
    class Texture;
    class Scene;
    class GameLayer;

    void HelperEventCallback(void *context, Engine::Event &e);
    //-----Forward Declarations-----//




    //Application Class.
    class Application
    {
        
        //Friends
        friend void HelperEventCallback(void *context, Engine::Event &e);

        friend class GameLayer;

        public:

        //Constructor and Deconstructor.
        Application();
        virtual ~Application();
        virtual Scene* EntryPoint() const = 0;

        //Run.
        void Run();

        //Get window.
        const Window& GetWindow() const; 

        //Push Layer.
        void PushLayer(Layer *);

        //Load Scene.
        void LoadScene(Scene* new_scene);
        
        //Create Texture.
        Texture* CreateTexture(const std::string &path, const std::string &unifrom_name="diffuse", bool flip=true);

        //-------------Inline Methods-------------//
        static inline Application& Get() { return *m_instance; }



        private:

        static Application *m_instance;

        std::vector<Layer*> m_layers;

        std::vector<Texture *> m_textures;

        Window *m_window;

        Scene *m_scene = nullptr;

        bool m_running = true;

        void EventsCallback(Event &e);

    };
}

#endif