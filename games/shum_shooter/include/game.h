#pragma once
#include "bn_core.h" 
#include "bn_string.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "common_info.h"
#include "assets.h"
#include <bn_log.h>
#include "bn_sprite_items_zig.h"
#include "bn_sprite_items_ball.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_palette_ptr.h"
#include "common_variable_8x8_sprite_font.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_bg.h"
#include "bn_random.h"

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
void display_game_over(bn::vector<bn::sprite_ptr, 32>& text_sprites, bn::sprite_text_generator& text_generator,game_state& game_state);
void display_pause(bn::vector<bn::sprite_ptr, 32>& text_sprites, bn::sprite_text_generator& text_generator, bn::sprite_ptr& ziggy, enemies& enemies_obj, bullets& bullets_obj, game_state& state, bool& paused);
void show_ziggy_and_bg(bn::sprite_ptr& ziggy, bn::regular_bg_ptr& bg);
void run_game(
    game_state& state,
    bn::regular_bg_ptr& bg,
    bn::sprite_ptr& ziggy,
    bn::sprite_text_generator& text_generator,
    bn::vector<bn::sprite_ptr, 32>& game_text_sprites,
    bn::random& random,
    bullets& bullets_obj,
    enemies& enemies_obj,
    bool& paused
);

void run_menu(
    bn::regular_bg_ptr& bg,
    bn::sprite_text_generator& text_generator,
    bn::vector<bn::sprite_ptr, 32>& menu_text_sprites
);
