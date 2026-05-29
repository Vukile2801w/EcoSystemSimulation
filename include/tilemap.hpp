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

        TileID getTile(int x, int y) const;
        void setTile(int x, int y, TileID id);

        void draw();
        Vector2 getOffset() const { return offset; }
        void setOffset(Vector2 newOffset) { offset = newOffset; }

        size_t getWidth() const;
        size_t getHeight() const;

    private:
        size_t width;
        size_t height;
        int tileSize;

        Vector2 offset;

        std::vector<TileID> tiles;
        std::shared_ptr<Graphics> g;
    };

    /// ===============================
    /// TileMapPrucudural Generation
    /// ===============================

    class TileMapGenerator
    {
    public:
        static std::unique_ptr<TileMap>
        generatePerlinNoiseMap(size_t width, size_t height, std::shared_ptr<Graphics> graphics, int tileSize = 32);
    };

} // namespace EcoSim

#endif // TILEMAP_HPP
