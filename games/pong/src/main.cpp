/*
    License for Butano:

    Copyright (c) 2020-2022 Gustavo Valiente gustavo.valiente@protonmail.com
    zlib License, see LICENSE file.
*/

// Butano libraries
#include "bn_core.h" // Core libraries.
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
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_palette_ptr.h"
#include "common_info.h"
#include "common_variable_8x8_sprite_font.h"

#include "bn_sprite_items_paddle.h"
#include "bn_sprite_items_ball.h"
#include "bn_regular_bg_items_bg.h"


struct enemy {
    int x;
    int y;
};

int main()
{
    // Initialization
    // Make sure that all initialized Butano data types are placed
    // AFTER this line is called.
    bn::core::init();
    
    // Plays the initial music on startup.
    // ...
    // Make sure that the 'music item' matches the name of an .xm or .mod file in /audio!
    // The '1' represents your volume. Its data type is "bn::fixed".
    // This means that you can put 'bn::fixed(0.5)' instead of '1'
    // if you want it to play at half-volume.
    bn::music_items::amayadori.play(1);

    // Create a background at position 0,0.
    // We can move it around, but we don't want to for now.
    // ...
    // Notice that we're creating a "ptr" (pointer) object, which is
    // populated with the output of an "item" object's create function.
    // 'sprite_ptr' != 'sprite_item'
    bn::regular_bg_ptr bg = bn::regular_bg_items::bg.create_bg(0, 0);

    // This creates the two paddles.
    // The GBA resolution is 240 x 160, which means that, for a 64x64 paddle,
    // You want their X values to be at about -140 and 140, respectively.
    bn::sprite_ptr left_paddle = bn::sprite_items::paddle.create_sprite(-140, 0);
    
    // We're flipping the right paddle, because the sprite is facing to the right.
    // It's important to save on sprites anywhere we can:
    // Don't forget: cartridges can only be around 16 MB in size!


    // Here are some variables to get us started.
    int score = 0;               // We'll add a point when you score, and deduct a point when you fail.
    int bullets_used = 0;
    const int max_enemies = 10;
    const int max_enemies_on_screen = 2;
    int enemies_on_screen = 0;
    constexpr int min_enemy_y_spacing = 16;
    // 'Delta' means change.
    // These two values represent, for each step of the gameloop,
    // which direction the ball should go. Negative means towards top-left, and positive is bottom-right.
    // For example,
    // delta_x = -1, delta_y = 1, would mean that the ball is moving towards the bottom-left side of the screen.
    // Increasing these numbers will make the ball move faster.

    // In Butano, as in many libraries, you need to initiatize an instance of a RANDOM object
    // in order to get random numbers. This is what we're doing here.
    bn::random random;

    // We'll want to set up a couple of Butano objects
    // in order to put text on the screen.
    bn::sprite_text_generator text_generator(common::variable_8x8_sprite_font);

    // A 'vector' is a data type that allows us to add or take away elements on a stack,
    // albeit a stack that can be accessed at any point. It's like an array, but it has
    // a built-in "size" value so that we can see how many elements are in it.
    // ..
    // We need to set up a vector of sprite_ptr to represent individual letters.
    // We can only have a max of 16 letters in this vector.
    bn::vector<bn::sprite_ptr, 16> text_sprites; 
    constexpr int max_bullets = 10;
    bn::vector<int, max_bullets> bullet_dx;
    bn::vector<bn::sprite_ptr, max_bullets> bullets;
    bn::vector<bn::sprite_ptr, max_enemies> enemies;
    bn::vector<int, max_enemies> enemy_dx;
    bn::vector<enemy, max_enemies> enemy_positions;
    for(int i = 0; i < max_bullets; ++i)
    {
        bullets.emplace_back(bn::sprite_items::ball.create_sprite(0, 0));
        bullets.back().set_visible(false);
        bullet_dx.emplace_back(0);
    }
    for(int i = 0; i < max_enemies; ++i)
    {
        enemies.emplace_back(bn::sprite_items::ball.create_sprite(0, 0));
        enemies.back().set_visible(false);
        enemy_dx.emplace_back(0);
        enemy_positions.emplace_back(enemy{0, 0});
    }
    while (true)
    {
        text_sprites.clear();
        bn::string<32> txt_score = "Score: " + bn::to_string<32>(score);
        bn::string<32> bullet_count_text = "Bullets: " + bn::to_string<32>(max_bullets-bullets_used)+"/" + bn::to_string<32>(max_bullets);
        bn::string<32> controls_text = "B to reload";
        text_generator.generate(-6 * 16, 70, controls_text, text_sprites);
        text_generator.generate(-6 * 16, -68, txt_score, text_sprites);
        text_generator.generate(30, -68, bullet_count_text, text_sprites);
        // If 'up' is being held, and we're not too far up,
        // Take our Y position and set it relative to where we currently are,
        // minus how far we want to move.
        if (bn::keypad::up_held() && left_paddle.y() > -48)
        {
            left_paddle.set_y(left_paddle.y() - 1);
        }

        else if (bn::keypad::down_held() && left_paddle.y() < 48)
        {
            left_paddle.set_y(left_paddle.y() + 1);
        }

   
       if(bn::keypad::a_pressed() && bullets_used < max_bullets)
            {
                BN_LOG(enemies_on_screen);
                for(int i = 0; i < bullets.size(); ++i)
                {
                    if(!bullets[i].visible())
                    {
                        bullets[i].set_position(left_paddle.x()+30, left_paddle.y());
                        BN_LOG("paddle position: ", left_paddle.x(), ", ", left_paddle.y());
                        BN_LOG("bullet position: ", bullets[i].x(), ", ", bullets[i].y());
                        bullets[i].set_visible(true);
                        bullet_dx[i] = 3;   // bullet speed
                        bn::sound_items::pong.play();
                        bullets_used++;
                        BN_LOG(bullets_used);
                        break;
                    }
                }
            }
        for(int i = 0; i < bullets.size(); ++i)
        {
            if(bullets[i].visible())
            {
                bullets[i].set_x(bullets[i].x() + bullet_dx[i]);

                if(bullets[i].x() > 140)
                {
                    bullets[i].set_visible(false);
                }
            }
        }
            
            // for(int i = 0; i < enemies.size(); ++i)
            // {
            //     if(enemies[i].visible())
            //     {
            //         enemies[i].set_x(enemy_positions[i].x);
            //         enemies[i].set_y(enemy_positions[i].y);
            //     }
            // }
        if (enemies_on_screen < max_enemies_on_screen){
            for(int i = 0; i < enemies.size(); ++i)
                {
                    if(!enemies[i].visible())
                    {
                        int rand_y = 0;
                        bool valid = false;

                        for(int attempt = 0; attempt < 8 && !valid; ++attempt)
                        {
                            rand_y = random.get_int(-48, 49);
                            valid = true;
                            for(int j = 0; j < enemies.size(); ++j)
                            {
                                if(enemies[j].visible())
                                {
                                    if(bn::abs(rand_y - enemies[j].y()) < min_enemy_y_spacing)
                                    {
                                        valid = false;
                                        break;
                                    }
                                }
                            }
                        }

                enemies[i].set_position(140, rand_y);
                enemies[i].set_visible(true);
                enemy_dx[i] = -1;

                enemies_on_screen++;
                BN_LOG(enemies_on_screen);
                break;
            }
        }
    }



       for(int i = 0; i < enemies.size(); ++i)
        {
            if(enemies[i].visible())
            {
                BN_LOG("enemy position: ", enemies[i].x(), ", ", enemies[i].y());
                enemies[i].set_x(enemies[i].x() + enemy_dx[i]);
                if(enemies[i].x() < -150)
                {
                    enemies[i].set_visible(false);
                    enemies_on_screen--;
                    BN_LOG(enemies_on_screen);
                }
            }
        }


        if (bn::keypad::b_pressed())
        {
            BN_LOG(score);
            bullets_used = 0;
            for(int i = 0; i < bullets.size(); ++i)
            {
                bullets[i].set_visible(false);
            }
        }

    
        // Do all the Butano things that we need to have done in the background.
        // If you don't call this, nothing will happen on the screen or through the speakers.
        bn::core::update();
    }
}

// And now we're done :)
// Good job!