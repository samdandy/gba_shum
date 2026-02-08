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
// Function declarations
bullets init_bullets();
enemies init_enemies();
void update_text_sprites(const game_state& state, bn::vector<bn::sprite_ptr, 32>& text_sprites, bn::sprite_text_generator& text_generator);
void reset_game_state(game_state& state, bullets& bullets, enemies& enemies);
void check_for_reload(game_state& state);
void check_up_input(bn::sprite_ptr& ziggy);
void check_down_input(bn::sprite_ptr& ziggy);
void check_for_shooting_bullet(game_state& state, bullets& bullets, bn::sprite_ptr& ziggy);
void check_player_input(game_state& state, bullets& bullets, bn::sprite_ptr& ziggy);
void spawn_enemies(game_state& state, enemies& enemies, bn::random& random);
void check_enemies(game_state& state, enemies& enemies, bn::sprite_ptr& ziggy);
void display_game_over(bn::vector<bn::sprite_ptr, 32>& text_sprites, bn::sprite_text_generator& text_generator);
void check_bullets(game_state& state, bullets& bullets, enemies& enemies);
void check_game_over(game_state& state);
void pause_game();
void run_game();