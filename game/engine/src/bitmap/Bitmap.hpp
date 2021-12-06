//
// Created by dzmitry on 05.12.2021.
//

#ifndef GAME_BITMAP_HPP
#define GAME_BITMAP_HPP

#include <string_view>
#include <vector>
#include <vec2.hpp>

class Bitmap
{
public:
    enum class Format
    {
        R,
        Rgb,
        Rgba,
        Rgba16F,
        Rgba32F,
        Rgb16F,
        Rgb32F,
    };

    Format getFormat() const;

    glm::vec2 getSize() const;


    explicit Bitmap(std::string_view filepath);

    const std::vector<unsigned char> &getImage() const;

private:
    Format _format;
    std::vector<unsigned char> _image;
    glm::vec2 _size;
};


#endif //GAME_BITMAP_HPP
