//
// Created by dzmitry on 18.11.2021.
//

#ifndef GAME_LINESCENE_HPP
#define GAME_LINESCENE_HPP


#include <IScene.hpp>
#include <memory>

class LineScene : public IScene
{
public:
    void draw() override;
    explicit LineScene(SDL_Window *window);
     ~LineScene();
private:
    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;
};


#endif //GAME_LINESCENE_HPP
