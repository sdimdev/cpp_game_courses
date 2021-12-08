//
// Created by dzmitry on 20.11.2021.
//

#include "SceneManager.hpp"

#include <utility>

struct SceneManager::Pimpl
{
    std::shared_ptr<IScene> currentScene = nullptr;
};


std::shared_ptr<IScene> SceneManager::getScene()
{
    return _pimpl->currentScene;
}

void SceneManager::setScene(std::shared_ptr<IScene> scene)
{
    _pimpl->currentScene = std::move(scene);
}
void SceneManager::drawScene()
{
    printf("SceneManager::drawScene\n");
    if (_pimpl->currentScene != nullptr)
    {
        printf("_pimpl->currentScene->draw()\n");
        _pimpl->currentScene->draw();
    }
}

SceneManager::SceneManager()
{
    _pimpl = std::make_unique<SceneManager::Pimpl>();
}

SceneManager::~SceneManager() = default;
