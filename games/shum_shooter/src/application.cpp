#include "application.h"

namespace shum
{
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
}