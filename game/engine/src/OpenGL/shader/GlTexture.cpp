//
// Created by dzmitry on 06.12.2021.
//

#include <GL/glew.h>
#include "GlTexture.hpp"
#include <common/Texture.hpp>
#include <cstdio>

namespace
{
    static bool logEnabled = true;

    void logMessage(char* message)
    {
        if (logEnabled)
            printf("%s\n", message);
    }

    GLenum getGlInternalFormat(Bitmap::Format bitmapFormat)
    {
        if (bitmapFormat == Bitmap::Format::R)
        {
            logMessage("getGlInternalFormat GL_R8");
            return GL_R8;
        }

        if (bitmapFormat == Bitmap::Format::Rgba32F || bitmapFormat == Bitmap::Format::Rgb32F)
        {
            logMessage("getGlInternalFormat GL_RGBA32F");
            return GL_RGBA32F;
        } else if (bitmapFormat == Bitmap::Format::Rgba16F)
        {
            logMessage("getGlInternalFormat GL_RGBA16F");
            return GL_RGBA16F;
        } else if (bitmapFormat == Bitmap::Format::Rgb16F)
        {
            logMessage("getGlInternalFormat GL_RGB16F");
            return GL_RGB16F;
        } else if (bitmapFormat == Bitmap::Format::Rgb)
        {
            logMessage("getGlInternalFormat GL_RGB");
            return GL_RGB;
        } else
        {
            logMessage("getGlInternalFormat GL_RGBA");
            return GL_RGBA;
        }
    }

    GLenum getGlFormat(Bitmap::Format bitmapFormat)
    {
        switch (bitmapFormat)
        {
            case Bitmap::Format::R:
                logMessage("getGlFormat GL_RED");
                return GL_RED;

            case Bitmap::Format::Rgb:
            case Bitmap::Format::Rgb16F:
            case Bitmap::Format::Rgb32F:
                logMessage("getGlFormat GL_RGB");
                return GL_RGB;

            case Bitmap::Format::Rgba:
            case Bitmap::Format::Rgba16F:
            case Bitmap::Format::Rgba32F:
                logMessage("getGlFormat GL_RGBA");
                return GL_RGBA;

        }
    }

    GLenum getGlType(Bitmap::Format bitmapFormat)
    {
        switch (bitmapFormat)
        {
            case Bitmap::Format::Rgb32F:
            case Bitmap::Format::Rgba32F:
                logMessage("getGlType GL_FLOAT");
                return GL_FLOAT;

            case Bitmap::Format::Rgb16F:
            case Bitmap::Format::Rgba16F:
                logMessage("getGlType GL_HALF_FLOAT");
                return GL_HALF_FLOAT;

            case Bitmap::Format::Rgb:
            case Bitmap::Format::Rgba:
            case Bitmap::Format::R:
                logMessage("getGlType GL_UNSIGNED_BYTE");
                return GL_UNSIGNED_BYTE;

        }
    }
}

GlTexture::GlTexture(Bitmap bitmap)
        : Texture(bitmap.getSize())
{
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);

    const auto glInternalFormat = getGlInternalFormat(bitmap.getFormat());
    const auto glType = getGlType(bitmap.getFormat());
    const auto glFormat = getGlFormat(bitmap.getFormat());

    glTexImage2D(GL_TEXTURE_2D, 0, glInternalFormat, bitmap.getSize().x, bitmap.getSize().y, 0,
                 glFormat, glType, bitmap.getImage().data());


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);
}

void GlTexture::active()
{
    glBindTexture(GL_TEXTURE_2D, _id);
}

GlTexture::~GlTexture() = default;