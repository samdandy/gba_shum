#pragma once
#include "layer.h"

namespace shum
{
    class Application
    {
    public:
        Application();
        void run();

        void set_layer(Layer* layer);
        void set_game_layer();
        void set_menu_layer();

        static Application& get_app();

    private:
        Layer* current_layer;
        GameLayer game_layer;
        MenuLayer menu_layer;
    };
}
