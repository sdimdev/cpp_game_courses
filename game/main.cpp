
#include "engine/src/Engine.hpp"
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
int main()
{
    Engine engine;
    engine.init();
    engine.showWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
    return 0;
}
