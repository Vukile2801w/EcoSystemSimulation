#include <texture.hpp>

namespace EcoSim
{
    Texture::Texture(const std::string &path)
    {
        load(path);
    }

    Texture::~Texture()
    {
        unload();
    }

    bool Texture::load(const std::string &path)
    {
        unload();
        texture = LoadTexture(path.c_str());
        loaded = texture.id != 0;
        return loaded;
    }

    void Texture::unload()
    {
        if (loaded)
        {
            UnloadTexture(texture);
            texture = {};
            loaded = false;
        }
    }

    bool Texture::isValid() const
    {
        return loaded;
    }

    int Texture::getWidth() const
    {
        return texture.width;
    }

    int Texture::getHeight() const
    {
        return texture.height;
    }

    const Texture2D &Texture::getNative() const
    {
        return texture;
    }

    // move ctor
    Texture::Texture(Texture &&other) noexcept
    {
        texture = other.texture;
        loaded = other.loaded;

        other.texture = {};
        other.loaded = false;
    }

    // move assign
    Texture &Texture::operator=(Texture &&other) noexcept
    {
        if (this != &other)
        {
            unload();
            texture = other.texture;
            loaded = other.loaded;

            other.texture = {};
            other.loaded = false;
        }
        return *this;
    }
}
