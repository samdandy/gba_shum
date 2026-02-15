#include "application.h"
#include <assert.h>

namespace shum
{

static Application* s_Application = nullptr;

Application::Application() :
    current_layer(nullptr)
{
    s_Application = this;
    set_menu_layer();  
}

void Application::run()
{
    while (true)
    {
        if (current_layer)
        {
            current_layer->update();
        }

        bn::core::update();
    }
}

void Application::set_layer(Layer* layer)
{
    current_layer = layer;
}

void Application::set_game_layer()
{
    set_layer(&game_layer);
}

void Application::set_menu_layer()
{
    set_layer(&menu_layer);
}

Application& Application::get_app()
{
    assert(s_Application);
    return *s_Application;
}

}
