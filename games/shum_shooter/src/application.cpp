#include "application.h"
#include <assert.h>

namespace shum
{

    static Application* s_Application = nullptr;
    
    Application::Application()
        : current_layer(nullptr), is_running(true)
    {
        s_Application = this;
    }

    
    void Application::run()
    {
        while (is_running)
        {
            if (current_layer)
            {
                current_layer->run_layer();
            }
        }
    }

    void Application::set_layer(Layer* layer)
    {
        current_layer = layer;
    }

    void Application::stop()
    {
        is_running = false;
    }
    Application& get_app(){
        assert(s_Application);
		return *s_Application;
    }
}