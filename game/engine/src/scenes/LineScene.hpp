//
// Created by dzmitry on 18.11.2021.
//

#ifndef GAME_LINESCENE_HPP
#define GAME_LINESCENE_HPP


#include <scenes/IScene.hpp>
#include <memory>
#include <list>
#include <renderer/IRenderer.hpp>
#include <domain/Line3f.hpp>

class LineScene : public IScene
{
public:
    void draw() override;
    bool handleEvent(WindowEvent event) override;
    explicit LineScene(IRenderer *renderer);
     ~LineScene();
private:
    IRenderer *renderer;
    std::list<Line3f> lp;
};


#endif //GAME_LINESCENE_HPP
