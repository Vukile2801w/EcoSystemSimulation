#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <vector>
#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <memory>
#include <string>

#include <texture.hpp>
#include <graphics.hpp>

namespace EcoSim
{
    using TileID = uint16_t;

    enum : TileID
    {
        TILE_AIR = 0
    };

    // ===============================
    // TileDefinition
    // ===============================

    struct TileDefinition
    {
        std::shared_ptr<Texture> texture;
        bool solid = false;
    };

    // ===============================
    // TileRegistry
    // ===============================

    class TileRegistry
    {
    public:
        static TileID registerTile(const TileDefinition &def);
        static TileID registerTile(const std::string &name, const TileDefinition &def);

        static const TileDefinition &get(TileID id);
        static TileID getID(const std::string &name);

    private:
        static std::unordered_map<TileID, TileDefinition> &registry();
        static std::unordered_map<std::string, TileID> &nameRegistry();

        static TileID nextID;
    };

    // ===============================
    // TileMap
    // ===============================

    class TileMap
    {
    public:
        TileMap(size_t w, size_t h, std::shared_ptr<Graphics> graphics, int tileSize = 32);

        bool loadTileMap(const std::string &filename);

        TileID getTile(size_t x, size_t y) const;
        void setTile(size_t x, size_t y, TileID id);

        void draw();

        size_t getWidth() const;
        size_t getHeight() const;

    private:
        size_t width;
        size_t height;
        int tileSize;

        std::vector<TileID> tiles;
        std::shared_ptr<Graphics> g;
    };

} // namespace EcoSim

#endif // TILEMAP_HPP
