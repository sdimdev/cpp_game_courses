//
// Created by dzmitry on 05.01.2022.
//

#ifndef GAME_RESOURCESMANAGER_HPP
#define GAME_RESOURCESMANAGER_HPP

#include <engine/Engine.hpp>
#include <map>
#include "common/IResourcesManager.hpp"

class ResourcesManager
{
public:
    std::shared_ptr<IResourcesManager<ITexture>> textures = std::make_shared<IResourcesManager<ITexture>>();
    std::shared_ptr<ITexture> getTexture(std::string_view path);
};


#endif //GAME_RESOURCESMANAGER_HPP
