//
// Created by dzmitry on 18.11.2021.
//

#include "ScenesFactory.hpp"
#include "utils/CommandLineUtil.cpp"
#include "LineScene.hpp"

ScenesFactory::ScenesFactory(int argc, char **argv)
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
}

std::unique_ptr<IScene> ScenesFactory::provideScene(IRenderer *renderer)
{
    switch (type)
    {
        case LINE:
            return std::make_unique<LineScene>(renderer);
        case SOFT_LINE:
            //todo
            return std::make_unique<LineScene>(renderer);
    }
}
