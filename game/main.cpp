
#include "engine/src/Engine.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char **argv)
{
    Engine engine;
    engine.init("CppCourses",
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                argc,
                argv);

    printf("INITED \n");
    while (engine.isActive())
    {
        engine.update();
    }
    return 0;
}
