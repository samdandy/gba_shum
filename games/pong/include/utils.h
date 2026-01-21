#ifndef UTILS_H
#define UTILS_H
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_bg.h"
#include "bn_sprite_items_paddle.h"
#include "bn_sprite_items_ball.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"
#include "bn_random.h"
#include "bn_sprite_text_generator.h"
#include "common_variable_8x8_sprite_font.h"
const int max_enemies = 10;
const int max_enemies_on_screen = 2;
const int min_enemy_y_spacing = 16;
const int max_bullets = 10;
const int max_lives = 5;
struct enemy_pos {
    int x;
    int y;
};

struct game_state {
    int score = 0;               
    int bullets_used = 0;
    int lives = max_lives;
    int enemies_on_screen = 0;
    bool game_over = false;
    
};

bn::regular_bg_ptr init_bg()
{
    bn::regular_bg_ptr bg = bn::regular_bg_items::bg.create_bg(0, 0);
    return bg;
}


void init_sprites(){
    
}

struct bullets {
    bn::vector<bn::sprite_ptr, 32> sprites;
    bn::vector<int, max_bullets> dx;
};

struct enemies {
    bn::vector<bn::sprite_ptr, 32> sprites;
    bn::vector<int, max_enemies> dx;
    bn::vector<enemy_pos, 32> positions;
};

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
        e.positions.emplace_back(enemy_pos{0, 0});
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

void display_game_over(bn::vector<bn::sprite_ptr, 32>& text_sprites, bn::sprite_text_generator& text_generator)
{
    text_sprites.clear();
    bn::string<32> game_over_text = "Game Over press a to play again";
    text_generator.generate(-6 * 16,0, game_over_text, text_sprites);
    bn::core::update();
}

void check_game_over(game_state& state)
{
    if(state.lives <= 0)
    {
        BN_LOG("Game Over");
        state.game_over = true;
    }
}

#endif 