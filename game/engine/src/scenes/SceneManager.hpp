//
// Created by dzmitry on 20.11.2021.
//

#ifndef GAME_SCENEMANAGER_HPP
#define GAME_SCENEMANAGER_HPP


#include <memory>
#include "IScene.hpp"

class SceneManager
{
public:
    explicit SceneManager();

    ~SceneManager();

    std::shared_ptr<IScene> getScene();

    void setScene(std::shared_ptr<IScene> scene);

    void drawScene();

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;
};


#endif //GAME_SCENEMANAGER_HPP
