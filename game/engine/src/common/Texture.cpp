//
// Created by dzmitry on 07.12.2021.
//

#include <vec2.hpp>
#include "Texture.hpp"

Texture::Texture(glm::vec2 size)
{
    this->size = size;
}

Texture::~Texture() = default;
