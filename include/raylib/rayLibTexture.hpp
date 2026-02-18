#ifndef RAYLIB_TEXTURE_HPP
#define RAYLIB_TEXTURE_HPP

#include <string>
#include <raylib.h>

namespace EcoSim
{
    class RaylibTexture : public Texture
    {
    public:
        RaylibTexture(const std::string &filePath);
        ~RaylibTexture();

        int getWidth() const;
        int getHeight() const;

        Texture2D &getNative();
        void GetTexture(void *textPtr);
        Texture2D GetTexture();

        bool isTextureLoaded() const;

    private:
        Texture2D texture;
        int width;
        int height;
    };

}

#endif