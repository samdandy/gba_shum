#include "Application.h"
#include "layer.h"
#include "bn_core.h"
shum::Application app; 
int main()
{
    bn::core::init();
    shum::GameLayer game_layer;
    shum::MenuLayer menu_layer;
    
    app.set_layer(&game_layer);
    app.run();
    
    return 0;
}

