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
    class Input;
    class Shader;

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

        //Create Shader.
        Shader* CreateShader(const std::string& vert_path, const std::string& frag_path);

        //-------------Inline Methods-------------//
        static inline Application& Get() { return *m_instance; }
        inline float GetDeltaTime() const { return m_deltaTime; }



        private:

        static Application *m_instance;

        std::vector<Layer*> m_layers;

        std::vector<Texture *> m_textures;

        std::vector<Shader *> m_shaders;

        Window *m_window;

        Scene *m_scene = nullptr;

        bool m_running = true;

        float m_deltaTime = 0;

        void EventsCallback(Event &e);

    };
}

#endif