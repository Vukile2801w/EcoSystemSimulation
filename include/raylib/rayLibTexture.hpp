#ifndef RAYLIB_TEXTURE_HPP
#define RAYLIB_TEXTURE_HPP

#include <string>
#include <raylib.h>

namespace EcoSim
{
    class RaylibTexture : public Texture
    {
    public:
        RaylibTexture();
        RaylibTexture(const std::string &filePath);
        virtual ~RaylibTexture();

        int getWidth();
        int getHeight();

        void GetTexture(void *buffer);
        Texture2D &getNative();

        bool isTextureLoaded();

    protected:
        Texture2D texture;
    };
}

#endif