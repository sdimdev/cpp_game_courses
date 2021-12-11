
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
    printf("SpritesScene::SpritesScene%d\n", engine != nullptr);
    std::shared_ptr<SpritesScene> scene = std::make_shared<SpritesScene>(engine);
    scene->node()->value = std::make_shared<SpriteData>(engine, "../engine/src/picture.jpeg");
    scene->node()->value->transformData.anchor = glm::vec2(0.5f, 0.5f);
    engine->sceneManager()->setScene(scene);
    engine->eventManager()->add(
            [&](std::shared_ptr<IWindowEvent> event)
            {
                auto keyboardEvent = std::dynamic_pointer_cast<KeyboardEvent>(event);
                if (keyboardEvent && keyboardEvent->action == DOWN)
                {
                    if (keyboardEvent->key == W)
                    {
                        scene->node()->value->transformData.rotation += 0.1f;
                        return true;
                    } else if (keyboardEvent->key == S)
                    {
                        scene->node()->value->transformData.rotation -= 0.1f;
                        return true;
                    }

                }
                return false;
            });

    while (engine->isActive())
    {
        engine->update();
        scene->node()->value->transformData.transform.reset();
        //scene->node()->value->transformData.rotation+=0.1f;
    }
    return 0;
}
