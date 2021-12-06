//
// Created by dzmitry on 18.11.2021.
//

#include "ScenesFactory.hpp"

#include <utility>
#include "utils/CommandLineUtil.cpp"
#include "LineScene.hpp"

struct ScenesFactory::Pimpl
{
    std::shared_ptr<IRenderer> renderer = nullptr;
};

ScenesFactory::ScenesFactory(std::shared_ptr<IRenderer> renderer)
{
    _pimpl = std::make_unique<ScenesFactory::Pimpl>();
    _pimpl->renderer = std::move(renderer);
}

IScene *ScenesFactory::createScene(int argc, char **argv)
{

    if (cmdOptionExists(argv, argv + argc, "-m"))
    {
        type = SOFT_LINE;
        printf("Mode\n");
    }

    char *scene = getCmdOption(argv, argv + argc, "-s");

    if (scene)
    {
        printf("Scene %s\n", scene);
    }

    switch (type)
    {
        case LINE:
            return new LineScene(_pimpl->renderer);
        case SOFT_LINE:
            //todo
            return new LineScene(_pimpl->renderer);
    }
}

ScenesFactory::~ScenesFactory() = default;
