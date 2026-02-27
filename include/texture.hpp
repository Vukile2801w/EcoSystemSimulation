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
        virtual float getWidth() const = 0;
        virtual float getHeight() const = 0;

        void GetTexture(void *buffer) {};

        virtual bool isTextureLoaded() const = 0;

    protected:
        float width;
        float height;
    };
}

#endif