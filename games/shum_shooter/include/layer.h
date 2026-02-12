#pragma once
#include "game.h"
#include "assets.h"

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
        game_state state;
        ~GameLayer() = default;
        void run_layer() override
        {
            run_game(state);  
        }
    };

}