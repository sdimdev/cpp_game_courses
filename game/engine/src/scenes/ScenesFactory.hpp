//
// Created by dzmitry on 18.11.2021.
//

#ifndef GAME_SCENESFACTORY_HPP
#define GAME_SCENESFACTORY_HPP


#include <scenes/IScene.hpp>
#include <memory>
#include <renderer/IRenderer.hpp>

class ScenesFactory
{
public:
    ScenesFactory(int argc, char **argv);
    std::unique_ptr<IScene> provideScene(IRenderer *renderer);
private:
    enum SCENE_TYPE
    {
        LINE, SOFT_LINE
    };
    SCENE_TYPE type = LINE;
};


#endif //GAME_SCENESFACTORY_HPP
