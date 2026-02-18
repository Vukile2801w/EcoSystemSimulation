#include <memory>
#include <iostream>

#include <rayLibGraphics.hpp>
#include <rayLibTexture.hpp>
#include <math.hpp>
#include <tilemap.hpp>
#include <rayLibInput.hpp>

int main()
{
    auto graphics = std::make_shared<EcoSim::RaylibGraphics>(800, 600, "My Window");
    graphics->backgroundColor = EcoSim::Color(36, 36, 35);

    auto input = std::make_shared<EcoSim::RayLibInput>();

    EcoSim::TileDefinition grassTile;
    grassTile.texture = std::make_shared<EcoSim::RaylibTexture>("../assets/grass.png");
    EcoSim::TileID grassTileID = EcoSim::TileRegistry::registerTile("grass", grassTile);

    EcoSim::TileDefinition mudTile;
    mudTile.texture = std::make_shared<EcoSim::RaylibTexture>("../assets/mud.png");
    EcoSim::TileID mudTileID = EcoSim::TileRegistry::registerTile("mud", mudTile);

    EcoSim::TileMap *map = new EcoSim::TileMap(25, 19, graphics, 32);
    map->loadTileMap("../assets/TileMap/map.tmx");

    while (graphics->isRunning())
    {
        input->handleInput();
        for (int i = 1; i < EcoSim::Input::Key::KEY_COUNT; i++)
        {
            EcoSim::Input::Key key = static_cast<EcoSim::Input::Key>(i);
            bool down = input->isKeyDown(key);
            bool released = input->isKeyReleased(key);
            bool pressed = input->isKeyPressed(key);
            if (released || pressed)
                std::cout << key << ": { Down: " << down << ", Released: " << released << ", Pressed: " << pressed << " }\n";
        }

        graphics->render();
    }

    return 0;
}
