
#include <engine/EngineFactory.hpp>
#include "engine/Engine.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char **argv)
{
    Engine engine = EngineFactory::create("CppCourses",
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                argc,
                argv);

    //engine.sceneManager().
    engine.

    while (engine.isActive())
    {
        engine.update();
    }
    return 0;
}
