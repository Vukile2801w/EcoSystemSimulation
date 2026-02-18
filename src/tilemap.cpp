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

        // Get tileset information
        tinyxml2::XMLElement *tileset = doc.FirstChildElement("map")->FirstChildElement("tileset");
        // Load tile definitions, parse as needed...

        // Get the layer
        tinyxml2::XMLElement *layer = doc.FirstChildElement("map")->FirstChildElement("layer");

        // Parse tile data
        const char *data = layer->FirstChildElement("data")->GetText();
        std::stringstream ss(data);

        size_t x = 0, y = 0;
        std::string tileID;

        while (std::getline(ss, tileID, ','))
        {
            // Assuming you already loaded the tile IDs into the TileRegistry
            EcoSim::TileID id = std::stoi(tileID);
            setTile(x, y, id);

            x++;
            if (x >= getWidth())
            {
                x = 0; // Move to the next row
                y++;
            }
        }

        return true;
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
                    (int)x * tileSize,
                    (int)y * tileSize};

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
