//
// Created by dzmitry on 18.11.2021.
//

#ifndef GAME_LINESCENE_HPP
#define GAME_LINESCENE_HPP


#include <scenes/IScene.hpp>
#include <memory>
#include <list>
#include <renderer/IRenderer.hpp>
#include <entity/Line3f.hpp>

class LineScene : public IScene
{
public:
    void draw() override;
    bool handleEvent(EventType eventType) override;
    explicit LineScene(IRenderer *renderer);
     ~LineScene() override;
private:
    IRenderer *renderer;
    std::list<Line3f> lp;
    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;
};


#endif //GAME_LINESCENE_HPP
