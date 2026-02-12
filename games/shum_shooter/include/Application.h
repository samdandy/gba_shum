#pragma once
#include "layer.h"

namespace shum
{
    class Application
    {
    public:
        Application();
        void run();
        void stop();
        void set_layer(Layer* layer);
        void set_game_layer();
        static Application& get_app();
    private:
        Layer* current_layer;
        bool is_running;
        shum::GameLayer game_layer;
    };
}