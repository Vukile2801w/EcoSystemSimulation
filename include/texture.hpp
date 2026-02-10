#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <raylib.h>

namespace EcoSim
{
    class Texture
    {
    public:
        Texture() = default;
        explicit Texture(const std::string &path);

        // RAII
        ~Texture();

        // zabrani copy (Texture2D ne treba kopirati)
        Texture(const Texture &) = delete;
        Texture &operator=(const Texture &) = delete;

        // dozvoli move
        Texture(Texture &&other) noexcept;
        Texture &operator=(Texture &&other) noexcept;

        bool load(const std::string &path);
        void unload();

        bool isValid() const;

        int getWidth() const;
        int getHeight() const;

        // pristup raw raylib teksturi
        const Texture2D &getNative() const;

    private:
        Texture2D texture{0};
        bool loaded = false;
    };
}

#endif
