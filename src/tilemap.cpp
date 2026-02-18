#include "TileMap.hpp"

namespace EcoSim
{
    // ===============================
    // Static member init
    // ===============================

    TileID TileRegistry::nextID = 1; // 0 = AIR

    // ===============================
    // TileRegistry
    // ===============================

    std::unordered_map<TileID, TileDefinition> &TileRegistry::registry()
    {
        static std::unordered_map<TileID, TileDefinition> instance;
        return instance;
    }

    std::unordered_map<std::string, TileID> &TileRegistry::nameRegistry()
    {
        static std::unordered_map<std::string, TileID> instance;
        return instance;
    }

    TileID TileRegistry::registerTile(const TileDefinition &def)
    {
        TileID id = nextID++;
        registry()[id] = def;
        return id;
    }

    TileID TileRegistry::registerTile(const std::string &name, const TileDefinition &def)
    {
        TileID id = nextID++;
        registry()[id] = def;
        nameRegistry()[name] = id;
        return id;
    }

    const TileDefinition &TileRegistry::get(TileID id)
    {
        return registry().at(id);
    }

    TileID TileRegistry::getID(const std::string &name)
    {
        return nameRegistry().at(name);
    }

    // ===============================
    // TileMap
    // ===============================

    TileMap::TileMap(size_t w, size_t h, std::shared_ptr<Graphics> graphics, int tileSize)
        : width(w), height(h), g(graphics), tileSize(tileSize)
    {
        tiles.resize(width * height, TILE_AIR);
        g->addDrawCallback([this]()
                           { draw(); });
    }

    TileID TileMap::getTile(size_t x, size_t y) const
    {
        if (x >= width || y >= height)
            return TILE_AIR;

        return tiles[y * width + x];
    }

    void TileMap::setTile(size_t x, size_t y, TileID id)
    {
        if (x >= width || y >= height)
            return;

        tiles[y * width + x] = id;
    }

    void TileMap::draw()
    {
        for (size_t y = 0; y < height; y++)
        {
            for (size_t x = 0; x < width; x++)
            {
                TileID id = tiles[y * width + x];
                if (id == TILE_AIR)
                    continue;

                const TileDefinition &def = TileRegistry::get(id);

                Vector2Int pos = {
                    x * tileSize,
                    y * tileSize};

                g->drawTexture(pos, *(def.texture));
            }
        }
    }

    size_t TileMap::getWidth() const
    {
        return width;
    }

    size_t TileMap::getHeight() const
    {
        return height;
    }

}
