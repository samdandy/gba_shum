#include "Application.h"
#include "bn_core.h"

int main()
{
    bn::core::init();
    shum::Application app;
    app.run();
}