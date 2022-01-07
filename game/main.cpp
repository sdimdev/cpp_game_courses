
#include <engine/EngineFactory.hpp>
#include <scenes/NodeScene.hpp>
#include <scenes/ScenesFactory.hpp>
#include "engine/Engine.hpp"
#include "entity/Sound.hpp"
#include "entity/TextureController.hpp"

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
    auto scene = std::make_shared<NodeScene>(engine);
    auto tank = std::make_shared<Sprite>(engine, "../textures/tank_body.png");
    auto pushka = std::make_shared<Sprite>(engine, "../textures/pushka.png");
    auto parentNode = std::make_shared<Node>();

    TextureController textureController(4, 4);
    for (int i = 0; i < 16; i++)
    {
        auto netSquad = std::make_shared<Sprite>(engine, "../textures/texture.jpg");
        netSquad->spriteData->transform.size = {140, 140};
        netSquad->spriteData->transform.scale = { 0.25f, 0.25f};
        netSquad->spriteData->transform.position = {140 * (i%4), 140 * (i/4)};
        textureController.chooseTextureMap(i, std::static_pointer_cast<ITextureMapSettable>(netSquad));
        parentNode->addChild(netSquad);
    }

    parentNode->addChild(tank);
    scene->setNode(parentNode);
    //scene->node()->(pushka)
    tank->spriteData->transform.anchor = glm::vec2(0.5f, 0.2f);
    tank->spriteData->transform.position = glm::vec2(300.0f, 300.0f);
    tank->spriteData->transform.scale = glm::vec2(0.2f, 0.2f);

    pushka->spriteData->transform.anchor = glm::vec2(0.5f, 0.2f);
    pushka->spriteData->transform.position = glm::vec2(tank->spriteData->transform.size.x * 0.5f,
                                                       tank->spriteData->transform.size.x * 0.5f);
    pushka->spriteData->transform.scale = glm::vec2(1.0f, 1.0f);

    tank->addChild(pushka);
    engine->sceneManager()->setScene(scene);
    engine->eventManager()->add(
            [&](std::shared_ptr<IWindowEvent> event)
            {
                auto keyboardEvent = std::dynamic_pointer_cast<KeyboardEvent>(event);
                if (keyboardEvent && keyboardEvent->action == DOWN)
                {
                    if (keyboardEvent->key == W)
                    {
                        pushka->spriteData->transform.rotation += 0.9f;
                        return true;
                    } else if (keyboardEvent->key == S)
                    {
                        pushka->spriteData->transform.rotation -= 0.9f;
                        return true;
                    }

                }
                return false;
            });
    // Sound sound("../engine/src/ot_attack.wav");

    while (engine->isActive())
    {
        engine->update();
        //scene->node()->value->transformData.rotation+=0.1f;
    }
    return 0;
}
