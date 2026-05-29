#include "TileMap.hpp"
#include <tinyxml2.h>
#include <iostream>
#include <sstream>
#include <perlin.hpp>
#include <cfloat>

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

    TileID TileMap::getTile(int x, int y) const
    {
        if (x < offset.x || y < offset.y ||
            (x - offset.x) >= width ||
            (y - offset.y) >= height)
        {
            return TILE_AIR;
        }

        return tiles[(y - offset.y) * width + (x - offset.x)];
    }

    void TileMap::setTile(int x, int y, TileID id)
    {
        if (x < offset.x || y < offset.y ||
            (x - offset.x) >= width ||
            (y - offset.y) >= height)
        {
            return;
        }

        tiles[(y - offset.y) * width + (x - offset.x)] = id;
    }

    void TileMap::draw()
    {
        auto cam = g->getCameraComponet();

        float zoom = cam->GetZoom();

        Vector2 size = g->getScreenSize();

        int visibleTilesX =
            (size.x / (tileSize * zoom)) + 2;

        int visibleTilesY =
            (size.y / (tileSize * zoom)) + 2;

        int centerTileX =
            (cam->pos.x / tileSize) - offset.x;

        int centerTileY =
            (cam->pos.y / tileSize) - offset.y;

        int startX = centerTileX - visibleTilesX / 2;
        int startY = centerTileY - visibleTilesY / 2;

        int endX = startX + visibleTilesX + 1;
        int endY = startY + visibleTilesY + 1;

        // clamp
        if (startX < 0)
            startX = 0;
        if (startY < 0)
            startY = 0;

        if (endX > (int)width)
            endX = width;
        if (endY > (int)height)
            endY = height;

        for (int y = startY; y < endY; y++)
        {
            for (int x = startX; x < endX; x++)
            {
                TileID id = tiles[y * width + x];

                if (id == TILE_AIR)
                    continue;

                const TileDefinition &def =
                    TileRegistry::get(id);

                Vector2Int pos =
                    {
                        (x + offset.x) * tileSize + tileSize,
                        (y + offset.y) * tileSize + tileSize};

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

    std::unique_ptr<EcoSim::TileMap>
    TileMapGenerator::generatePerlinNoiseMap(
        size_t width,
        size_t height,
        std::shared_ptr<Graphics> graphics,
        int tileSize)
    {
        auto map =
            std::make_unique<TileMap>(
                width,
                height,
                graphics,
                tileSize);

        ValueNoise2D perlin = ValueNoise2D(7, 0.4, 2);

        // Pre svega, zelim se izviniti samome sebi ako ikad se vratim ovde
        // Ali sada je 22:34 29.05.2026 i sutra je republicko takmicenje
        // Nemam vremena da acctually uradim ovo kako treba. Tako da `screw u`
        // ID's ce biti hardcoded na osnovu redosleda u tilemap atlasu
        // 🫸🫷🫸🫷🥀🥀 ne vracaj se ovde. God Help

        TileID grass[] = {4, 5, 6, 7, 8};
        TileID flowers[] = {1, 2, 3};

        std::vector<float> noiseMap(width * height);

        float minNoise = FLT_MAX;
        float maxNoise = FLT_MIN;

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                float n = perlin.generate(
                    x * 0.8f,
                    y * 0.8f);

                noiseMap[y * width + x] = n;

                minNoise = std::min(minNoise, n);
                maxNoise = std::max(maxNoise, n);
            }
        }

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                float n = noiseMap[y * width + x];

                n = (n - minNoise) / (maxNoise - minNoise);

                if (n < 0.7f)
                {
                    map->setTile(x, y, grass[rand() % 5]);
                }
                else
                {
                    map->setTile(x, y, flowers[rand() % 3]);
                }
            }
        }

        std::cout << "Perlin Noise Generated | Min: " << minNoise << " | Max: " << maxNoise << std::endl;

        map->setOffset({-(int)width / 2, -(int)height / 2});

        return map;
    }
}
