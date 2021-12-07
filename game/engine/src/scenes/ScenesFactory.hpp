//
// Created by dzmitry on 18.11.2021.
//

#ifndef GAME_SCENESFACTORY_HPP
#define GAME_SCENESFACTORY_HPP


#include <scenes/IScene.hpp>
#include <memory>
#include <common/IRenderer.hpp>
#include <engine/Engine.hpp>

class ScenesFactory
{
public:
    ScenesFactory(std::shared_ptr<IRenderer> renderer);

    ~ScenesFactory();

    std::shared_ptr<IScene> createScene(int argc, char **argv); //todo add params
private:
    enum SCENE_TYPE
    {
        LINE, SOFT_LINE
    };
    SCENE_TYPE type = LINE;
    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;
};


#endif //GAME_SCENESFACTORY_HPP
