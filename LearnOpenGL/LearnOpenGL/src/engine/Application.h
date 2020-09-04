#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H
#include <vector>



namespace Engine
{   

    //-----Forward Declarations-----//
    class Layer;
    class Window;
    //-----Forward Declarations-----//


    //Application Class.
    class Application
    {
        public:

        //Constructor and Deconstructor.
        Application();
        virtual ~Application();

        //Run.
        void Run();

        //Push Layer.
        void PushLayer(Layer *);



        private:

        std::vector<Layer*> *m_layers;

        Window *m_window;

        bool m_running = true;

    };
}

#endif