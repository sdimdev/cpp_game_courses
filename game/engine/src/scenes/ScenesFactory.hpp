//
// Created by dzmitry on 18.11.2021.
//

#ifndef GAME_SCENESFACTORY_HPP
#define GAME_SCENESFACTORY_HPP


#include <scenes/IScene.hpp>
#include <memory>
#include <common/renderer/IRenderer.hpp>

class ScenesFactory
{
public:
    explicit ScenesFactory(IRenderer *renderer, int argc, char **argv);
    ~ScenesFactory();
    IScene* createScene(); //todo add params
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
