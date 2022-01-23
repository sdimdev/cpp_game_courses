//
// Created by dzmitry on 01.12.2021.
//

#include <SDL_rwops.h>
#include <string_view>
#include <string>
#include <stdexcept>
#include <vector>
#include <SDL_opengl.h>
#include "stb_image.cpp"

static unsigned char *load(std::string_view filepath, GLint *width, GLint *height, int * channels)
{
    static GLuint texture;         /* Texture object */

    SDL_RWops *file = SDL_RWFromFile(filepath.data(), "rb");
    if (file == nullptr)
    {
        throw std::runtime_error("Filed to open file: " + std::string(filepath));
    }
    Sint64 length = SDL_RWsize(file);
    std::vector<unsigned char> data(length);
    SDL_RWread(file, data.data(), length, 1);
    SDL_RWclose(file);

    stbi_set_flip_vertically_on_load(false);
    auto img = stbi_load_from_memory(data.data(), data.size(), width, height, channels, 0);
    printf("size of image data: %d\n", data.size());
    if (img == nullptr)
    {
        throw std::runtime_error("unsupported file format: " + std::string(filepath));
    }
    return img;
}

static void freeImg(unsigned char *img)
{
    stbi_image_free(img);
}