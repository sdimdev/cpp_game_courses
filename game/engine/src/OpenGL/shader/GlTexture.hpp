//
// Created by dzmitry on 06.12.2021.
//

#ifndef GAME_GLTEXTURE_HPP
#define GAME_GLTEXTURE_HPP

#include <bitmap/Bitmap.hpp>
#include <common/Texture.hpp>

class GlTexture : public Texture
{
public:
    explicit GlTexture(Bitmap bitmap);
    ~GlTexture();
    void active();

private:
    uint32_t _id;
};


#endif //GAME_GLTEXTURE_HPP
