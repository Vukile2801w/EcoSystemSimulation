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
        virtual ~Texture() {};

        void GetTexture(void *buffer) {};

    protected:
        int width;
        int height;
    };
}

#endif