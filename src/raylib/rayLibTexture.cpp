#include "raylibTexture.hpp"
#include <iostream>

namespace EcoSim
{
    RaylibTexture::RaylibTexture(const std::string &path)
    {
        texture = LoadTexture(path.c_str());
        width = texture.width;
        height = texture.height;
    }

    RaylibTexture::~RaylibTexture()
    {
        UnloadTexture(texture);
    }

    int RaylibTexture::getWidth() const
    {
        return width;
    }

    int RaylibTexture::getHeight() const
    {
        return height;
    }

    // Ako imate void GetTexture(void *textPtr) ovde
    void RaylibTexture::GetTexture(void *textPtr) // Izmijenite prema potpisu u headeru
    {
        if (!isTextureLoaded())
            std::cerr << "Texture is not loaded\n";
        *static_cast<Texture2D **>(textPtr) = &texture;
    }

    Texture2D RaylibTexture::GetTexture()
    {
        if (!isTextureLoaded())
            std::cerr << "Texture is not loaded\n";
        return texture;
    }

    Texture2D &RaylibTexture::getNative()
    {
        return texture;
    }

    bool RaylibTexture::isTextureLoaded() const // dodajte const
    {
        return texture.id > 0;
    }
}
