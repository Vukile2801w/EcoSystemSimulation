#include "raylibTexture.hpp"
#include <iostream>

namespace EcoSim
{

    // ----------------------------------------------------
    // Constructors
    // ----------------------------------------------------

    RaylibTexture::RaylibTexture() = default;

    RaylibTexture::RaylibTexture(const std::string &path)
    {
        texture = LoadTexture(path.c_str());
        width = texture.width;
        height = texture.height;
    }

    RaylibTexture::RaylibTexture(Texture2D tex)
    {
        texture = tex;
        width = tex.width;
        height = tex.height;
    }

    // ----------------------------------------------------
    // Destructor
    // ----------------------------------------------------

    RaylibTexture::~RaylibTexture()
    {
        if (texture.id != 0)
            UnloadTexture(texture);
    }

    // ----------------------------------------------------
    // Move Constructor
    // ----------------------------------------------------

    RaylibTexture::RaylibTexture(RaylibTexture &&other) noexcept
    {
        texture = other.texture;
        width = other.width;
        height = other.height;

        other.texture.id = 0;
        other.width = 0;
        other.height = 0;
    }

    // ----------------------------------------------------
    // Move Assignment
    // ----------------------------------------------------

    RaylibTexture &RaylibTexture::operator=(RaylibTexture &&other) noexcept
    {
        if (this != &other)
        {
            if (texture.id != 0)
                UnloadTexture(texture);

            texture = other.texture;
            width = other.width;
            height = other.height;

            other.texture.id = 0;
            other.width = 0;
            other.height = 0;
        }
        return *this;
    }

    // ----------------------------------------------------
    // Basic API
    // ----------------------------------------------------

    float RaylibTexture::getWidth() const
    {
        return width;
    }

    float RaylibTexture::getHeight() const
    {
        return height;
    }

    Texture2D &RaylibTexture::getNative()
    {
        return texture;
    }

    Texture2D RaylibTexture::GetTexture() const
    {
        return texture;
    }

    bool RaylibTexture::isTextureLoaded() const
    {
        return texture.id != 0;
    }

    RaylibTexture RaylibTexture::copyToOtherTexture(Vector4 src, Vector4 dest)
    {
        RenderTexture2D target = LoadRenderTexture((int)dest.z, (int)dest.w);

        BeginTextureMode(target);
        ClearBackground(BLANK);

        Rectangle srcRect = {src.x, src.y, src.z, src.w};
        Rectangle destRect = {dest.x, dest.y, dest.z, dest.w};

        DrawTexturePro(texture, srcRect, destRect, {0, 0}, 0.0f, WHITE);

        EndTextureMode();

        // Fallback for older raylib: create Image from texture, then new Texture2D
        Image img = LoadImageFromTexture(target.texture);
        Texture2D newTexture = LoadTextureFromImage(img);

        UnloadImage(img);
        UnloadRenderTexture(target);

        return RaylibTexture(newTexture);
    }

    // Hardened isImageEmpty: clamp rect and validate indexes
    bool RaylibTexture::isImageEmpty(Texture tex, Vector4 rect)
    {
        if (rect == Vector4{0, 0, 0, 0})
        {
            rect = {0, 0, (float)tex.width, (float)tex.height};
        }

        Image img = LoadImageFromTexture(tex);
        if (img.data == nullptr)
            return true;

        // Clamp rect to image bounds
        int startX = std::max(0, (int)rect.x);
        int startY = std::max(0, (int)rect.y);
        int width = std::max(0, (int)rect.z);
        int height = std::max(0, (int)rect.w);

        if (startX >= img.width || startY >= img.height)
        {
            UnloadImage(img);
            return true;
        }
        if (startX + width > img.width)
            width = img.width - startX;
        if (startY + height > img.height)
            height = img.height - startY;
        if (width <= 0 || height <= 0)
        {
            UnloadImage(img);
            return true;
        }

        Color *pixels = LoadImageColors(img);
        bool empty = true;

        for (int y = 0; y < height && empty; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int idx = (startY + y) * img.width + (startX + x);
                if (idx < 0 || idx >= img.width * img.height)
                    continue;
                if (pixels[idx].a > 0)
                {
                    empty = false;
                    break;
                }
            }
        }

        UnloadImageColors(pixels);
        UnloadImage(img);

        return empty;
    }

    // ----------------------------------------------------
    // Atlas Loader
    // ----------------------------------------------------

    std::vector<std::shared_ptr<RaylibTexture>>
    RaylibTexture::loadTextureAtlas(const std::string &filePath, Vector2Int tileSize)
    {
        std::vector<std::shared_ptr<RaylibTexture>> textures;

        auto atlas = std::make_shared<RaylibTexture>(filePath);

        if (!atlas->isTextureLoaded())
        {
            std::cerr << "Failed to load atlas: " << filePath << std::endl;
            return textures;
        }

        int xCount = (int)atlas->getWidth() / tileSize.x;
        int yCount = (int)atlas->getHeight() / tileSize.y;

        for (int y = 0; y < yCount; y++)
        {
            for (int x = 0; x < xCount; x++)
            {
                Vector4 rect = {
                    (float)(x * tileSize.x),
                    (float)(y * tileSize.y),
                    (float)tileSize.x,
                    (float)tileSize.y};

                if (!isImageEmpty(atlas->GetTexture(), rect))
                {
                    auto tileTex = std::make_shared<RaylibTexture>(
                        atlas->copyToOtherTexture(rect, {0, 0, (float)tileSize.x, (float)tileSize.y}));

                    if (tileTex->isTextureLoaded())
                        textures.push_back(tileTex);
                }
            }
        }

        return textures;
    }

}