#include <raylibTexture.hpp>
#include <cassert>

namespace EcoSim
{
    RaylibTexture::RaylibTexture(const std::string &path)
    {
        texture = LoadTexture(path.c_str());
    }

    RaylibTexture::~RaylibTexture()
    {
        UnloadTexture(texture);
    }

    int RaylibTexture::getWidth()
    {
        width = texture.width;
        return width;
    }

    int RaylibTexture::getHeight()
    {
        height = texture.height;
        return height;
    }

    void RaylibTexture::GetTexture(void *textPtr)
    {
        textPtr = &texture;
    }

    Texture2D &RaylibTexture::getNative()
    {
        return texture;
    }

    bool RaylibTexture::isTextureLoaded()
    {
        return texture.id <= 0;
    }
}
