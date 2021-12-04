//
// Created by dzmitry on 01.12.2021.
//

#ifndef GAME_TEXTURELOADER_HPP
#define GAME_TEXTURELOADER_HPP


#include <SDL_rwops.h>
#include <string_view>
#include <stdexcept>
#include <vector>
#include <SDL_opengl.h>
#include "../libs/stbi/stb_image.cpp"

class TextureLoader
{
    public:
    GLenum      type;            /* Texture type */
    GLuint      texture;         /* Texture object */
    GLint      width;         /* Texture width */
    GLint      height;         /* Texture height */
    void load(std::string_view filepath)
    {
        SDL_RWops *file = SDL_RWFromFile(filepath.data(), "rb");
        if (file == nullptr)
        {
            throw std::runtime_error("Filed to open file: " + std::string(filepath));
        }
        Sint64 length = SDL_RWsize(file);
        std::vector<unsigned char> data(length);
        SDL_RWread(file, data.data(), length, 1);
        SDL_RWclose(file);

        int ch;
        stbi_set_flip_vertically_on_load(false);
        auto img = stbi_load_from_memory(data.data(), data.size(), &width, &height, &ch, 0);
        if (img == nullptr)
        {
            throw std::runtime_error("unsupported file format: " + std::string(filepath));
        }

        type = GL_TEXTURE_2D;
        // Create and bind a texture object
        glGenTextures(1, &texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);/*
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);*/

        auto internal_format = [&](){
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

        auto format = [&](){
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

        stbi_image_free(img);
    }
};


#endif //GAME_TEXTURELOADER_HPP
