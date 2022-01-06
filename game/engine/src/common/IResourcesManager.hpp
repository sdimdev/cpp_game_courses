//
// Created by dzmitry on 05.01.2022.
//

#ifndef GAME_IRESOURCESMANAGER_HPP
#define GAME_IRESOURCESMANAGER_HPP

#include "ITexture.hpp"
#include <memory>
#include <map>

class IResourcesManager
{
public:
    ~IResourcesManager() = default;

    virtual std::shared_ptr<ITexture> getTexture(std::string_view path) = 0;
};

#endif //GAME_IRESOURCESMANAGER_HPP
