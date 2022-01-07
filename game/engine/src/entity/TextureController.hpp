//
// Created by dzmitry on 06.01.2022.
//

#ifndef GAME_TEXTURECONTROLLER_HPP
#define GAME_TEXTURECONTROLLER_HPP

#include <cstdint>
#include <memory>
#include "ITextureMapSettable.hpp"

class TextureController
{
public:
    explicit TextureController(uint32_t countx, uint32_t county);

    void chooseTextureMap(uint32_t num, std::shared_ptr<ITextureMapSettable> textureMapSettable);

private:
    uint32_t countx;
    uint32_t county;
    uint32_t maxNum;
    float item_size_x;
    float item_size_y;
};


#endif //GAME_TEXTURECONTROLLER_HPP
