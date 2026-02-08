#pragma once
#include "layer.h"

namespace shum
{
    class Application
    {
    public:
        Application() : current_layer(nullptr), is_running(true) {}

        void run();
        void stop();
        void set_layer(Layer* layer);

    private:
        Layer* current_layer;
        bool is_running;
    };
}