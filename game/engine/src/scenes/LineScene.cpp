//
// Created by dzmitry on 18.11.2021.
//

#include <entity/Line3f.hpp>
#include <entity/Point3f.hpp>
#include <shader/LensPointShader.hpp>
#include <utils/TimeInteractor.hpp>
#include <shader/LensPixelShader.hpp>
#include "LineScene.hpp"

struct LineScene::Pimpl
{
    LensPointShader *shader = nullptr;
    LensPixelShader *pixelShader = nullptr;
    int64_t lastTime = 0;
    int64_t dtime = 0;
    bool need_draw = true;
    float xspeed = 5;
    float yspeed = 3;
    int64_t frame_time = 50;
};

void LineScene::draw()
{
    if (_pimpl->need_draw)
    {
        _pimpl->need_draw = false;
        renderer->startDrawing();
        std::list<Line3f>::iterator it;
        for (it = lp.begin(); it != lp.end(); ++it)
            renderer->drawLine(*it, _pimpl->shader, _pimpl->pixelShader);
        renderer->endDrawing();
    }
}

bool LineScene::handleEvent(EventType eventType)
{
    //todo refactor that
    int64_t currtime = TimeInteractor::currentTimeMillisecond();
    int64_t dt = currtime - _pimpl->lastTime;
    //printf("%d\n", dt);
    _pimpl->lastTime = currtime;
    _pimpl->dtime += dt;
    if (_pimpl->dtime > _pimpl->frame_time)
    {
        _pimpl->need_draw = true;
        _pimpl->dtime -= _pimpl->frame_time;
        Point3f p = _pimpl->shader->getPoint() += Point3f(_pimpl->xspeed, _pimpl->yspeed);
        if (p.getX() < 0 && _pimpl->xspeed < 0)
        {
            _pimpl->xspeed *= -1;
        }
        if (p.getX() > 640 && _pimpl->xspeed > 0)
        {
            _pimpl->xspeed *= -1;
        }
        if (p.getY() < 0 && _pimpl->yspeed < 0)
        {
            _pimpl->yspeed *= -1;
        }
        if (p.getY() > 480 && _pimpl->yspeed > 0)
        {
            _pimpl->yspeed *= -1;
        }
        _pimpl->shader->moveToPoint(p);
        _pimpl->pixelShader->moveToPoint(p);
    }
    return false;
}

LineScene::LineScene(IRenderer *renderer)
{
    //todo refactor that
    _pimpl = std::make_unique<LineScene::Pimpl>();
    Point3f point3F = Point3f(300.0, 300.0);
    _pimpl->shader = new LensPointShader(point3F, 100);
    _pimpl->pixelShader = new LensPixelShader(point3F, 100);
    _pimpl->lastTime = TimeInteractor::currentTimeMillisecond();
    const int di = 10;
    const int dj = 10;
    const int endi = 400;
    const int endj = 400;
    const int marginTop = 50;
    const int marginLeft = 100;
    this->renderer = renderer;
    for (int i = 0; i <= endi; i += di)
    {
        if (i != 0)
        {
            for (int j = 0; j <= endj; j += dj)
            {
                if (j != endj)

                    lp.emplace_back(
                            Point3f(marginLeft + i, marginTop + j),
                            Point3f(marginLeft + i, marginTop + j + dj)
                    );
                if (i != endi)
                    lp.emplace_back(
                            Point3f(marginLeft + i, marginTop + j),
                            Point3f(marginLeft + i + di, marginTop + j)
                    );
            }
        }
    }
}

LineScene::~LineScene() = default;