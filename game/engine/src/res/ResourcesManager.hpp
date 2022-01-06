//
// Created by dzmitry on 05.01.2022.
//

#ifndef GAME_RESOURCESMANAGER_HPP
#define GAME_RESOURCESMANAGER_HPP

#include <engine/Engine.hpp>
#include <map>
#include "common/IResourcesManager.hpp"

class ResourcesManager : public IResourcesManager
{
public:
    std::shared_ptr<ITexture> getTexture(std::string_view path) override;

protected:
    std::map<std::string_view, std::shared_ptr<ITexture>> textureMap;
};


#endif //GAME_RESOURCESMANAGER_HPP
