#pragma once
#include "game.h"
#include "assets.h"

namespace shum
{
    class Layer
    {
    public:
        virtual ~Layer() = default;
        virtual void update() = 0;   
    };

    class GameLayer : public Layer
    {
    public:
        GameLayer();
        void update() override;
    private:
        game_state state;
        bn::regular_bg_ptr bg;
        bn::sprite_ptr ziggy;
        bn::sprite_text_generator text_generator;
        bn::vector<bn::sprite_ptr, 32> game_text_sprites;
        bn::random random;
        bullets bullets_obj;
        enemies enemies_obj;
        bool paused;
    };

    class MenuLayer : public Layer
    {
    public:
        MenuLayer();
        void update() override;
    private:
        bn::regular_bg_ptr title_bg;
    };
}