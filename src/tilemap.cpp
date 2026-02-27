#include "TileMap.hpp"
#include <tinyxml2.h>
#include <iostream>
#include <sstream>

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

        offset = {0, 0};

        tiles.resize(width * height, TILE_AIR);
        g->addDrawCallback([this]()
                           { draw(); });
    }

    bool TileMap::loadTileMap(const std::string &filename)
    {
        tinyxml2::XMLDocument doc;
        if (doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS)
        {
            std::cerr << "Failed to load map file: " << filename << std::endl;
            return false;
        }

        tinyxml2::XMLElement *mapElement = doc.FirstChildElement("map");
        if (!mapElement)
            return false;

        tinyxml2::XMLElement *layer = mapElement->FirstChildElement("layer");
        if (!layer)
            return false;

        tinyxml2::XMLElement *dataElement = layer->FirstChildElement("data");
        if (!dataElement)
            return false;

        // Initialize offsets
        offset.x = 0;
        offset.y = 0;

        int minX = INT_MAX;
        int minY = INT_MAX;
        int maxX = INT_MIN;
        int maxY = INT_MIN;

        for (tinyxml2::XMLElement *chunk = dataElement->FirstChildElement("chunk");
             chunk;
             chunk = chunk->NextSiblingElement("chunk"))
        {
            int chunkX = chunk->IntAttribute("x");
            int chunkY = chunk->IntAttribute("y");
            int chunkWidth = chunk->IntAttribute("width");
            int chunkHeight = chunk->IntAttribute("height");

            if (chunkX < minX)
                minX = chunkX;
            if (chunkY < minY)
                minY = chunkY;

            if (chunkX + chunkWidth > maxX)
                maxX = chunkX + chunkWidth;
            if (chunkY + chunkHeight > maxY)
                maxY = chunkY + chunkHeight;
        }

        if (minX == INT_MAX || minY == INT_MAX)
            return false;

        // Proceed with setting offsets
        offset.x = minX;
        offset.y = minY;

        width = maxX - minX;
        height = maxY - minY;

        tiles.clear();
        tiles.resize(width * height, TILE_AIR);

        // ===============================
        // 2️⃣ Učitaj tile podatke
        // ===============================

        for (tinyxml2::XMLElement *chunk = dataElement->FirstChildElement("chunk");
             chunk;
             chunk = chunk->NextSiblingElement("chunk"))
        {
            int chunkX = chunk->IntAttribute("x");
            int chunkY = chunk->IntAttribute("y");
            int chunkWidth = chunk->IntAttribute("width");

            const char *data = chunk->GetText();
            if (!data)
                continue;

            std::stringstream ss(data);
            std::string tileID;

            int tileX = 0;
            int tileY = 0;

            while (std::getline(ss, tileID, ','))
            {
                if (tileID.empty())
                    continue;

                int id = std::stoi(tileID);

                int globalX = chunkX + tileX;
                int globalY = chunkY + tileY;

                int localX = globalX - offset.x;
                int localY = globalY - offset.y;

                if (localX >= 0 && localY >= 0 &&
                    localX < (int)width &&
                    localY < (int)height)
                {
                    tiles[localY * width + localX] = (TileID)id;
                }

                tileX++;
                if (tileX >= chunkWidth)
                {
                    tileX = 0;
                    tileY++;
                }
            }
        }

        std::cout << "Map loaded: "
                  << width << "x" << height
                  << " | Offset: (" << offset.x << ", " << offset.y << ")"
                  << std::endl;

        return true;
    }

    TileID TileMap::getTile(size_t x, size_t y) const
    {
        if (x < offset.x || y < offset.y ||
            static_cast<size_t>(x - offset.x) >= width ||
            static_cast<size_t>(y - offset.y) >= height)
        {
            return TILE_AIR;
        }

        return tiles[(y - offset.y) * width + (x - offset.x)];
    }

    void TileMap::setTile(size_t x, size_t y, TileID id)
    {
        if (x < offset.x || y < offset.y ||
            static_cast<size_t>(x - offset.x) >= width ||
            static_cast<size_t>(y - offset.y) >= height)
        {
            return;
        }

        tiles[(y - offset.y) * width + (x - offset.x)] = id;
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
                    (int)(x + offset.x) * tileSize,
                    (int)(y + offset.y) * tileSize};

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
