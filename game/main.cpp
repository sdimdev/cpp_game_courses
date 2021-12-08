
#include <engine/EngineFactory.hpp>
#include <scenes/SpitesScene.hpp>
#include <scenes/ScenesFactory.hpp>
#include "engine/Engine.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char **argv)
{
    std::shared_ptr<Engine> engine = EngineFactory::create("CppCourses",
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                argc,
                argv);

    //std::shared_ptr<ScenesFactory> factory = std::make_shared<ScenesFactory>(engine.shared_from_this());
    std::shared_ptr<SpritesScene> scene = std::make_shared<SpritesScene>(engine);
    scene->node()->value = std::make_shared<SpriteData>(engine, "../engine/src/picture.jpeg");
    engine->sceneManager()->setScene(scene);

    while (engine->isActive())
    {
        engine->update();
    }
    return 0;
}
