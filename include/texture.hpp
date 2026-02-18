#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

namespace EcoSim
{
    class Texture
    {
    public:
        Texture() {};
        Texture(const std::string filePath) {};

        virtual ~Texture() = default;
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;

        void GetTexture(void *buffer) {};

        virtual bool isTextureLoaded() const = 0;

    protected:
        int width;
        int height;
    };
}

#endif