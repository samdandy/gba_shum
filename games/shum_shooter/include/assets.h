#pragma once
#include "bn_sprite_ptr.h"
#include "bn_vector.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_bg.h"
#include "bn_sprite_items_zig.h"
#include "bn_sprite_items_ball.h"
#include "bn_random.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_palette_ptr.h"
#include "common_variable_8x8_sprite_font.h"

constexpr int max_enemies = 10;
constexpr int max_enemies_on_screen = 2;
constexpr int min_enemy_y_spacing = 16;
constexpr int max_bullets = 10;
constexpr int max_lives = 5;
constexpr int enemy_hitbox = 12;

struct game_state {
    int score = 0;               
    int bullets_used = 0;
    int lives = max_lives;
    int enemies_on_screen = 0;
    bool game_over = false;
    
};

struct bullets {
    bn::vector<bn::sprite_ptr, 32> sprites;
    bn::vector<int, max_bullets> dx;
};

struct enemies {
    bn::vector<bn::sprite_ptr, 32> sprites;
    bn::vector<int, max_enemies> dx;
};