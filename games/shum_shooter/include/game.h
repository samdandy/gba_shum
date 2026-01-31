#pragma once
#include "bn_core.h" 
#include "bn_string.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "common_info.h"
#include "assets.h"
#include "bn_random.h"
#include "bn_sprite_items_zig.h"
#include "bn_sprite_items_ball.h"
#include "bn_sprite_items_paddle.h"

bullets init_bullets()
{
    bullets b;
    for(int i = 0; i < max_bullets; ++i)
    {
        b.sprites.emplace_back(bn::sprite_items::ball.create_sprite(0, 0));
        b.sprites.back().set_visible(false);
        b.dx.emplace_back(0);
    }
    return b;
}

enemies init_enemies()
{
    enemies e;
    for(int i = 0; i < max_enemies; ++i)
    {
        e.sprites.emplace_back(bn::sprite_items::ball.create_sprite(0, 0));
        e.sprites.back().set_visible(false);
        e.dx.emplace_back(0);
    }
    return e;
}

void update_text_sprites(const game_state& state, bn::vector<bn::sprite_ptr, 32>& text_sprites, bn::sprite_text_generator& text_generator)
{
    text_sprites.clear();
    bn::string<32> txt_score = "Score: " + bn::to_string<32>(state.score);
    bn::string<32> bullet_count_text = "Bullets: " + bn::to_string<32>(max_bullets-state.bullets_used)+"/" + bn::to_string<32>(max_bullets);
    bn::string<32> controls_text = "B to Reload";
    bn::string<32> lives_text = "Lives: " + bn::to_string<32>(state.lives);
    text_generator.generate(-6 * 16, 70, controls_text, text_sprites);
    text_generator.generate(-6 * 16, -68, txt_score, text_sprites);
    text_generator.generate(30, -68, bullet_count_text, text_sprites);
    text_generator.generate(30, -56, lives_text, text_sprites);
}


void reset_game_state(game_state& state, bullets& bullets, enemies& enemies)
{
    state.game_over = false;
    state.score = 0;
    state.bullets_used = 0;
    state.lives = max_lives;
    state.enemies_on_screen = 0;
    for(int i = 0; i < bullets.sprites.size(); ++i) 
    {
        bullets.sprites[i].set_visible(false);
    }
    for(int i = 0; i < enemies.sprites.size(); ++i)
    {
        enemies.sprites[i].set_visible(false);
    }
}

void check_for_reload(game_state& state)
{
    if (bn::keypad::b_pressed())
        {
            state.bullets_used = 0;
        }
}

void check_up_input(bn::sprite_ptr& ziggy){
    if(bn::keypad::up_held() && ziggy.y() > -48)
        {
            ziggy.set_y(ziggy.y() - 3);
        }  
}

void check_down_input(bn::sprite_ptr& ziggy){
    if(bn::keypad::down_held() && ziggy.y() < 48)
    {
        ziggy.set_y(ziggy.y() + 3);
    }
}

void check_for_shooting_bullet(game_state& state, bullets& bullets, bn::sprite_ptr& ziggy)
{
    if(bn::keypad::a_pressed() && state.bullets_used < max_bullets)
    {
        for(int i = 0; i < bullets.sprites.size(); ++i)
        {
            if(!bullets.sprites[i].visible())
            {
                bullets.sprites[i].set_position(ziggy.x()+15, ziggy.y());
                bullets.sprites[i].set_visible(true);
                bullets.dx[i] = 3;   
                state.bullets_used++;
                break;
            }
        }
    }
}

void check_player_input(game_state& state, bullets& bullets, bn::sprite_ptr& ziggy)
{
    check_up_input(ziggy);
    check_down_input(ziggy);
    check_for_reload(state); 
    check_for_shooting_bullet(state, bullets, ziggy);
}


void spawn_enemies(game_state& state, enemies& enemies, bn::random& random)
{
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
                break;
            }
        }
    }
}

void check_enemies(game_state& state, enemies& enemies, bn::sprite_ptr& ziggy)
{
    for(int i = 0; i < enemies.sprites.size(); ++i)
        {
            if(enemies.sprites[i].visible())
            {
                enemies.sprites[i].set_x(enemies.sprites[i].x() + enemies.dx[i]);

                if(enemies.sprites[i].x() < -160)
                {
                    enemies.sprites[i].set_visible(false);
                    state.enemies_on_screen--;
                    state.lives--;
                }
                if(enemies.sprites[i].x() > ziggy.x() - enemy_hitbox && enemies.sprites[i].x() < ziggy.x() + enemy_hitbox && enemies.sprites[i].y() > ziggy.y() - enemy_hitbox && enemies.sprites[i].y() < ziggy.y() + enemy_hitbox)
                {
                    enemies.sprites[i].set_visible(false);
                    state.enemies_on_screen--;
                    state.lives--;
                }

            }
        }
}

void display_game_over(bn::vector<bn::sprite_ptr, 32>& text_sprites, bn::sprite_text_generator& text_generator)
{
    text_sprites.clear();
    bn::string<32> game_over_text = "Game Over press a to play again";
    text_generator.generate(-6 * 16,0, game_over_text, text_sprites);
    bn::core::update();
}



void check_bullets(game_state& state, bullets& bullets, enemies& enemies)
{
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
                    if(enemies.sprites[j].visible() && bullets.sprites[i].x() > enemies.sprites[j].x() - enemy_hitbox && bullets.sprites[i].x() < enemies.sprites[j].x() + enemy_hitbox && bullets.sprites[i].y() > enemies.sprites[j].y() - enemy_hitbox && bullets.sprites[i].y() < enemies.sprites[j].y() + enemy_hitbox)
                    {
                        enemies.sprites[j].set_visible(false);
                        bullets.sprites[i].set_visible(false);
                        state.enemies_on_screen--;
                        state.score++;
                    }
                }
            }
        }
}


void check_game_over(game_state& state)
{
    if(state.lives <= 0)
    {
        state.game_over = true;
    }
}


void main_game_loop()
{
    bn::core::init();

    bn::regular_bg_ptr bg = bn::regular_bg_items::bg.create_bg(0, 0);
    bn::sprite_ptr ziggy = bn::sprite_items::zig.create_sprite(-108, 0);
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
        else{
        check_game_over(state);
        check_player_input(state, bullets, ziggy);
        check_bullets(state, bullets, enemies);
        spawn_enemies(state, enemies, random);
        check_enemies(state, enemies, ziggy);
        }
    bn::core::update();
    }
}
