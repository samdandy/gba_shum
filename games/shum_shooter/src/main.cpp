/*
    License for Butano:

    Copyright (c) 2020-2022 Gustavo Valiente gustavo.valiente@protonmail.com
    zlib License, see LICENSE file.
*/

// Butano libraries
#include "bn_core.h" 
#include "bn_log.h"
#include "bn_sram.h"
#include "bn_music.h"
#include "bn_music_actions.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"
#include "bn_sram.h"
#include "bn_math.h"
#include "bn_string.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_random.h"

#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_palette_ptr.h"
#include "common_info.h"
#include "common_variable_8x8_sprite_font.h"



#include "utils.h"

int main()
{
    // Initialization
    // Make sure that all initialized Butano data types are placed
    // AFTER this line is called.
    // The GBA resolution is 240 x 160, which means that, for a 64x64 paddle,
    bn::core::init();
    bn::regular_bg_ptr bg = init_bg();
    bn::sprite_ptr left_paddle = bn::sprite_items::paddle.create_sprite(-140, 0);
    bn::sprite_text_generator text_generator(common::variable_8x8_sprite_font);
    bn::vector<bn::sprite_ptr, 32> text_sprites;
    bn::random random;

    game_state state;
    bullets bullets = init_bullets();
    enemies enemies = init_enemies();

    while (true)
    {
        
        update_text_sprites(state, text_sprites, text_generator);
        if (state.game_over)
        {
            display_game_over(text_sprites, text_generator);
            if (bn::keypad::a_pressed())
            {
                reset_game_state(state, bullets, enemies);
            }
            continue;
        }  
        
        
        check_game_over(state);
        if (bn::keypad::up_held() && left_paddle.y() > -48)
        {
            left_paddle.set_y(left_paddle.y() - 3);
        }

        else if (bn::keypad::down_held() && left_paddle.y() < 48)
        {
            left_paddle.set_y(left_paddle.y() + 3);
        }

   
       if(bn::keypad::a_pressed() && state.bullets_used < max_bullets)
            {
                BN_LOG(state.enemies_on_screen);
                for(int i = 0; i < bullets.sprites.size(); ++i)
                {
                    if(!bullets.sprites[i].visible())
                    {
                        bullets.sprites[i].set_position(left_paddle.x()+30, left_paddle.y());
                        BN_LOG("paddle position: ", left_paddle.x(), ", ", left_paddle.y());
                        BN_LOG("bullet position: ", bullets.sprites[i].x(), ", ", bullets.sprites[i].y());
                        bullets.sprites[i].set_visible(true);
                        bullets.dx[i] = 3;   // bullet speed
                        bn::sound_items::pong.play();
                        state.bullets_used++;
                        BN_LOG(state.bullets_used);
                        break;
                    }
                }
            }
        for(int i = 0; i < bullets.sprites.size(); ++i)
        {
            if(bullets.sprites[i].visible())
            {
                bullets.sprites[i].set_x(bullets.sprites[i].x() + bullets.dx[i]);

                if(bullets.sprites[i].x() > 140)
                {
                    bullets.sprites[i].set_visible(false);
                }
                for(int j = 0; j < enemies.sprites.size(); ++j)
                {
                    if(enemies.sprites[j].visible() && bullets.sprites[i].x() > enemies.sprites[j].x() - 8 && bullets.sprites[i].x() < enemies.sprites[j].x() + 8 && bullets.sprites[i].y() > enemies.sprites[j].y() - 8 && bullets.sprites[i].y() < enemies.sprites[j].y() + 8)
                    {
                        enemies.sprites[j].set_visible(false);
                        bullets.sprites[i].set_visible(false);
                        state.enemies_on_screen--;
                        state.score++;
                        BN_LOG("shot: ", state.score);
                    }
                }
            }
        }
            
        if (state.enemies_on_screen < max_enemies_on_screen){
            for(int i = 0; i < enemies.sprites.size(); ++i)
                {
                    if(!enemies.sprites[i].visible())
                    {
                        int rand_y = 0;
                        bool valid = false;

                        for(int attempt = 0; attempt < 8 && !valid; ++attempt)
                        {
                            rand_y = random.get_int(-48, 49);
                            valid = true;
                            for(int j = 0; j < enemies.sprites.size(); ++j)
                            {
                                if(enemies.sprites[j].visible())
                                {
                                    if(bn::abs(rand_y - enemies.sprites[j].y()) < min_enemy_y_spacing)
                                    {
                                        valid = false;
                                        break;
                                    }
                                }
                            }
                        }

                enemies.sprites[i].set_position(random.get_int(140, 500), rand_y);
                enemies.sprites[i].set_visible(true);
                enemies.dx[i] = random.get_int(-2,-1);
                state.enemies_on_screen++;
                BN_LOG(state.enemies_on_screen);
                break;
            }
        }
    }
       for(int i = 0; i < enemies.sprites.size(); ++i)
        {
            if(enemies.sprites[i].visible())
            {
                enemies.sprites[i].set_x(enemies.sprites[i].x() + enemies.dx[i]);
                if(enemies.sprites[i].x() < -150)
                {
                    enemies.sprites[i].set_visible(false);
                    state.enemies_on_screen--;
                    state.lives--;
                    BN_LOG(state.enemies_on_screen);
                }
                
            }
        }
        if (bn::keypad::b_pressed())
        {
            BN_LOG(state.score);
            state.bullets_used = 0;
            for(int i = 0; i < bullets.sprites.size(); ++i)
            {
                bullets.sprites[i].set_visible(false);
            }
        }
    bn::core::update();
    }

}

