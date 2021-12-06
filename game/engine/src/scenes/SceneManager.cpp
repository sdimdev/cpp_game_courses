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
    return _pimpl->currentScene = std::move(std::shared_ptr<IScene>);
}
void SceneManager::drawScene()
{
    if (_pimpl->currentScene != nullptr)
    {
        _pimpl->currentScene->draw();
    }
}

SceneManager::SceneManager()
{
    _pimpl = std::make_unique<SceneManager::Pimpl>();
}

SceneManager::~SceneManager() = default;
