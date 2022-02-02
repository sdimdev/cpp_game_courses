//
// Created by dzmitry on 05.01.2022.
//

#include "ResourcesManager.hpp"
#include <OpenGL/shader/GlTexture.hpp>

std::shared_ptr<ITexture> ResourcesManager::getTexture(std::string_view path)
{
    return textures->resourceForName(std::string(path), [&](){
        Bitmap bitmap(path);
        return std::make_shared<GlTexture>(std::move(bitmap) );
    });
}
