//
// Created by dzmitry on 19.11.2021.
//

#ifndef GAME_ENGINEFACTORY_HPP
#define GAME_ENGINEFACTORY_HPP


#include "Engine.hpp"

class EngineFactory
{
public:
    static std::shared_ptr<Engine> create(std::string_view window_name, int width, int height, int argc, char **argv);
};


#endif //GAME_ENGINEFACTORY_HPP
