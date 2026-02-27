#ifndef RAYLIB_TEXTURE_HPP
#define RAYLIB_TEXTURE_HPP

#include <string>
#include <vector>
#include <memory>
#include <raylib.h>
#include <math.hpp>

namespace EcoSim
{
    class RaylibTexture : public Texture
    {
    public:
        // ---- Constructors ----
        RaylibTexture();
        explicit RaylibTexture(const std::string &filePath);
        explicit RaylibTexture(Texture2D tex);

        // ---- Rule of 5 ----
        ~RaylibTexture();

        RaylibTexture(const RaylibTexture &) = delete;
        RaylibTexture &operator=(const RaylibTexture &) = delete;

        RaylibTexture(RaylibTexture &&other) noexcept;
        RaylibTexture &operator=(RaylibTexture &&other) noexcept;

        // ---- Public API ----
        float getWidth() const;
        float getHeight() const;

        Texture2D &getNative();
        Texture2D GetTexture() const;

        bool isTextureLoaded() const;

        RaylibTexture copyToOtherTexture(Vector4 src, Vector4 dest);

        static bool isImageEmpty(Texture tex, Vector4 rect = {0, 0, 0, 0});

        static std::vector<std::shared_ptr<RaylibTexture>>
        loadTextureAtlas(const std::string &filePath, Vector2Int tileSize);

    private:
        Texture2D texture{};
        float width = 0;
        float height = 0;
    };
}

#endif