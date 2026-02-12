#include "Application.h"
#include "layer.h"
#include "bn_core.h"
#include "game.h"

int main()
{
    shum::Application app; 
    bn::core::init(); 
    app.set_game_layer();
    app.run();
    return 0;
}

