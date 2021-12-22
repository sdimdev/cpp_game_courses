
#include <engine/EngineFactory.hpp>
#include <scenes/SpitesScene.hpp>
#include <scenes/ScenesFactory.hpp>
#include "engine/Engine.hpp"
#include "entity/Sound.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//********FOR DEBUGGING CHANGE logDebug IN ENGINE.hpp******// todo fix it ^__^

int main(int argc, char **argv)
{
    std::shared_ptr<Engine> engine = EngineFactory::create("have you ever played being blind?",
                                                           SCREEN_WIDTH,
                                                           SCREEN_HEIGHT,
                                                           argc,
                                                           argv);

    //std::shared_ptr<ScenesFactory> factory = std::make_shared<ScenesFactory>(engine.shared_from_this());
    printf("SpritesScene::SpritesScene%d\n", engine != nullptr);
    std::shared_ptr<SpritesScene> scene = std::make_shared<SpritesScene>(engine);
    std::shared_ptr<SpriteData> tank = std::make_shared<SpriteData>(engine, "../engine/src/tank_body.png");
    std::shared_ptr<SpriteData> pushka = std::make_shared<SpriteData>(engine, "../engine/src/pushka.png");
    scene->node()->value = tank;
    //scene->node()->(pushka)
    tank->transformData.anchor = glm::vec2(0.5f, 0.2f);
    tank->transformData.position = glm::vec2(300.0f, 300.0f);
    tank->transformData.scale = glm::vec2(0.2f, 0.2f);

    pushka->transformData.anchor = glm::vec2(0.5f, 0.2f);
    pushka->transformData.position =  glm::vec2(tank->transformData.size.x * 0.5f, tank->transformData.size.x * 0.5f);
    pushka->transformData.scale = glm::vec2(1.0f, 1.0f);

    std::shared_ptr<Node<SpriteData>> pushkaNode = std::make_shared<Node<SpriteData>>(pushka);
    scene->node()->addChild(pushkaNode);
    engine->sceneManager()->setScene(scene);
    engine->eventManager()->add(
            [&](std::shared_ptr<IWindowEvent> event)
            {
                auto keyboardEvent = std::dynamic_pointer_cast<KeyboardEvent>(event);
                if (keyboardEvent && keyboardEvent->action == DOWN)
                {
                    if (keyboardEvent->key == W)
                    {
                        pushka->transformData.rotation += 0.9f;
                        return true;
                    } else if (keyboardEvent->key == S)
                    {
                        pushka->transformData.rotation -= 0.9f;
                        return true;
                    }

                }
                return false;
            });
   // Sound sound("../engine/src/ot_attack.wav");

    while (engine->isActive())
    {
        engine->update();
        scene->node()->value->transformData.transform.reset();
        //scene->node()->value->transformData.rotation+=0.1f;
    }
    return 0;
}
