//
// Created by dzmitry on 05.01.2022.
//

#include "ResourcesManager.hpp"
#include <OpenGL/shader/GlTexture.hpp>

std::shared_ptr<ITexture> ResourcesManager::getTexture(std::string_view path)
{
    std::shared_ptr<ITexture> result = textureMap[path];
    if (result == nullptr)
    {
        Bitmap bitmap(path);
        result = std::make_shared<GlTexture>(std::move(bitmap) );
        textureMap[path] = result;
    }
    return result;
}
