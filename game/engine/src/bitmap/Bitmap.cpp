//
// Created by dzmitry on 05.12.2021.
//

#include <stdexcept>
#include "Bitmap.hpp"
#include  <utils/TextureLoader.cpp>

Bitmap::Bitmap(std::string_view filepath)
{
    GLint width, height;
    int channels;
/*    GLenum type = GL_TEXTURE_2D;
    GLuint texture;*/
    unsigned char *img = load(filepath, &width, &height, &channels);
    if (img == nullptr)
    {
        throw std::runtime_error("unsupported file format: " + std::string{filepath});
    }

    auto getFmt = [](int ch)
    {
        switch (ch)
        {
            case 1:
                printf("Format::R\n");
                return Format::R;
            case 3:
                printf("Format::Rgb\n");
                return Format::Rgb;
            case 4:
                printf("Format::Rgba\n");
                return Format::Rgba;

            default:
                throw std::invalid_argument("Incorect chanels size from TGA");
        }
    };

    _format = getFmt(channels);
    auto imgSize = width * height * channels;

    //TODO: no copy
    _image = {img, img + imgSize};

    _size = glm::vec2(width, height);


    /*
     * // Create and bind a texture object
    glGenTextures(1, &texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    auto internal_format = [&]()
    {
        switch (ch)
        {
            case 1:
                return GL_R8;
            case 2:
                return GL_RG;
            case 3:
                return GL_RGB;
            case 4:
                return GL_RGBA;
        }
    }();

    auto format = [&]()
    {
        switch (ch)
        {
            case 1:
                return GL_RED;
            case 2:
                return GL_RG;
            case 3:
                return GL_RGB;
            case 4:
                return GL_RGBA;
        }
    }();

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 internal_format, //в зависимости от количества каналов в ch
                 width, height, 0, format, GL_UNSIGNED_BYTE, img);
    */

    freeImg(img);
}

const std::vector<unsigned char> &Bitmap::getImage() const
{
    return _image;
}

Bitmap::Format Bitmap::getFormat() const
{
    return _format;
}

glm::vec2 Bitmap::getSize() const
{
    return _size;
}