#pragma once
#include "game.h"

namespace shum
{
    class Layer
    {
    public:
        virtual ~Layer() = default;
        virtual void run_layer() = 0;  
    };

    class GameLayer : public Layer
    {
    public:
        void run_layer() override
        {
            run_game();  
        }
    };
    
    class MenuLayer : public Layer
    {
    public:
        void run_layer() override
        {
            pause_game();  
        }
    };
}