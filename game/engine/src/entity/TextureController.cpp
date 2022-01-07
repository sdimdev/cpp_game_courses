//
// Created by dzmitry on 06.01.2022.
//

#include "TextureController.hpp"

TextureController::TextureController(uint32_t countx, uint32_t county)
{
    this->countx = countx <= 0 ? 1 : countx;
    this->county = county <= 0 ? 1 : county;

    this->maxNum = this->countx * this->county;
    this->item_size_x = 1.0f / this->countx;
    this->item_size_y = 1.0f / this->county;
}

void TextureController::chooseTextureMap(uint32_t num, std::shared_ptr<ITextureMapSettable> textureMapSettable)
{
    if (num < 0 || num >= maxNum)
    {
        return;
    }
    int posx = num % countx;
    int posy = num / county;

    textureMapSettable->setTexturePoint1(glm::vec2(posx * item_size_x, posy * item_size_y));
    textureMapSettable->setTexturePoint2(glm::vec2((posx + 1) * item_size_x, (posy + 1) * item_size_y));
}
