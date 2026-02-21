#include "layer.h"
#include "application.h"
#include "game.h"

namespace shum
{

    GameLayer::GameLayer() 
        : bg(bn::regular_bg_items::bg.create_bg(0, 0)),
        ziggy(bn::sprite_items::zig.create_sprite(-108, 0)),
        text_generator(common::variable_8x8_sprite_font),
        bullets_obj(init_bullets()),
        enemies_obj(init_enemies()),
        paused(false)
    {
        ziggy.set_visible(false);
        reset_game_state(state, bullets_obj, enemies_obj);
    }

    void GameLayer::update()
    {
        run_game(state, bg, ziggy, text_generator, game_text_sprites, 
                random, bullets_obj, enemies_obj, paused);
    }

    MenuLayer::MenuLayer() 
        : title_bg(bn::regular_bg_items::title_bg.create_bg(0, 0))
    {
    }

    void MenuLayer::update()
    {
        run_menu(title_bg);
    }

}