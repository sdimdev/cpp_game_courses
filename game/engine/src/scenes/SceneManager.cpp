//
// Created by dzmitry on 20.11.2021.
//

#include "SceneManager.hpp"

struct SceneManager::Pimpl
{
    IScene *currentScene = nullptr;
    ScenesFactory *scenesFactory = nullptr;
};


IScene *SceneManager::getScene()
{
    return _pimpl->currentScene;
}

void SceneManager::drawScene()
{
    IScene *scene = _pimpl->currentScene;
    if (scene != nullptr)
    {
        scene->draw();
    }
}

SceneManager::SceneManager(ScenesFactory *scenesFactory)
{
    _pimpl = std::make_unique<SceneManager::Pimpl>();
    _pimpl->scenesFactory = scenesFactory;
    _pimpl->currentScene = scenesFactory->createScene();
}

SceneManager::~SceneManager() = default;
