//
// Created by dzmitry on 18.11.2021.
//

#ifndef GAME_SCENESFACTORY_HPP
#define GAME_SCENESFACTORY_HPP


#include <IScene.hpp>
#include <SDL.h>
#include <memory>

class ScenesFactory
{
public:
    ScenesFactory(int argc, char **argv);
    std::unique_ptr<IScene> provideScene(SDL_Window *window);
private:
    enum SCENE_TYPE
    {
        LINE, SOFT_LINE
    };
    SCENE_TYPE type = LINE;
};


#endif //GAME_SCENESFACTORY_HPP
