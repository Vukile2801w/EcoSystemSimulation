#include <memory>
#include <raylibGraphics.hpp>
#include <rayLibTexture.hpp>
#include <math.hpp>
#include <iostream>
#include <tilemap.hpp>

#include <math.h>

class testEntity : public std::enable_shared_from_this<testEntity>
{
public:
    std::shared_ptr<EcoSim::RaylibGraphics> g;
    std::shared_ptr<EcoSim::Texture> tex;

    EcoSim::Vector2 pos;
    EcoSim::Vector2 dir = EcoSim::Vector2(1, 1);

    testEntity(std::shared_ptr<EcoSim::RaylibGraphics> g, const std::string &texPath, EcoSim::Vector2 pos)
        : g(g), tex(std::make_shared<EcoSim::RaylibTexture>(texPath)), pos(pos)
    {
        g->addDrawCallback([this]()
                           {
            auto sharedThis = shared_from_this(); // Ovde dolazi iz bez .lock()
            sharedThis->draw(); });
    }

    void draw()
    {
        pos.x += dir.x;
        pos.y += dir.y;

        std::cerr << "Position: (" << pos.x << ", " << pos.y << ")" << std::endl;

        if (!tex)
        {
            std::cerr << "Texture pointer is null." << std::endl;
            return;
        }

        if (!g)
        {
            std::cerr << "Graphics pointer is null." << std::endl;
            return;
        }

        g->drawTexture(pos, *tex);

        if (pos.x > g->getScreenSize().x - tex->getWidth() || pos.x < 0)
            dir.x *= -1;
        if (pos.y > g->getScreenSize().y - tex->getHeight() || pos.y < 0)
            dir.y *= -1;
    }
};

int main()
{
    auto graphics = std::make_shared<EcoSim::RaylibGraphics>(800, 600, "My Window");
    graphics->backgroundColor = EcoSim::Color(36, 36, 35);

    EcoSim::TileDefinition grassTile;
    grassTile.texture = std::make_shared<EcoSim::RaylibTexture>("../assets/grass.png");
    EcoSim::TileID grassTileID = EcoSim::TileRegistry::registerTile("grass", grassTile);

    EcoSim::TileDefinition mudTile;
    mudTile.texture = std::make_shared<EcoSim::RaylibTexture>("../assets/mud.png");
    EcoSim::TileID mudTileID = EcoSim::TileRegistry::registerTile("mud", mudTile);

    EcoSim::TileMap map(25, 19, graphics, 32);
    for (size_t y = 0; y < map.getHeight(); ++y)
    {
        for (size_t x = 0; x < map.getWidth(); ++x)
        {
            bool V = (x + y) % 2 == 0;

            if (V)
            {
                map.setTile(x, y, mudTileID);
            }
            else
            {
                map.setTile(x, y, grassTileID);
            }
        }
    }

    // auto e = std::make_shared<testEntity>(graphics, "../assets/logo.jpg", EcoSim::Vector2(5, 5));

    while (graphics->isRunning())
    {
        graphics->render();
    }

    return 0;
}
