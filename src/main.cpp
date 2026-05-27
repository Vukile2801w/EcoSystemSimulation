#include <memory>
#include <iostream>

#include <rayLibGraphics.hpp>
#include <rayLibTexture.hpp>
#include <math.hpp>
#include <tilemap.hpp>
#include <rayLibInput.hpp>
#include <time.hpp>
#include <entityManager.hpp>
#include <creature.hpp>


int main()
{

    auto graphics = std::make_shared<EcoSim::RaylibGraphics>(800, 600, "My Window");
    graphics->backgroundColor = EcoSim::Color(36, 36, 35);

    auto cam = graphics->getCameraComponet();
    auto time = graphics->getTimeComponet();

    auto input = std::make_shared<EcoSim::RayLibInput>();

    std::vector<std::shared_ptr<EcoSim::RaylibTexture>> textures = EcoSim::RaylibTexture::loadTextureAtlas("C:/Users/wukbg/programing/C++/EcoSystemSimulation/build/assets/tilemap.png", {32, 32});
    for (int i = 0; i < textures.size(); i++)
    {
        EcoSim::TileDefinition tile = EcoSim::TileDefinition();
        tile.texture = textures[i];
        EcoSim::TileID tileID = EcoSim::TileRegistry::registerTile(tile);
        std::cout
            << " Registered tile " << i << " with ID: " << tileID << std::endl;
    }

    EcoSim::TileMap *map = new EcoSim::TileMap(25, 19, graphics, 32);
    map->loadTileMap("C:/Users/wukbg/programing/C++/EcoSystemSimulation/build/assets/TileMap/map.tmx");

    EcoSim::EntityManager entityManager(graphics, time);
    

    for (int i = 0; i < 5; i++)
    {
        entityManager.createEntity<EcoSim::Creature>(EcoSim::Vector2(i * 50 + 100, -200));
    }
    std::cout << "Created 5 creatures." << std::endl;

#define SPEED 100.0f
#define ZOOM_SPEED .2f
    while (graphics->isRunning())
    {
        input->handleInput();

        if (input->isKeyDown(EcoSim::Input::KEY_A))
            cam->pos.x -= SPEED * time->GetDeltaTime();
        if (input->isKeyDown(EcoSim::Input::KEY_D))
            cam->pos.x += SPEED * time->GetDeltaTime();

        if (input->isKeyDown(EcoSim::Input::KEY_W))
            cam->pos.y -= SPEED * time->GetDeltaTime();
        if (input->isKeyDown(EcoSim::Input::KEY_S))
            cam->pos.y += SPEED * time->GetDeltaTime();

        if (input->isMouseButtonPressed(EcoSim::Input::MOUSE_SCROLL_UP) || input->isMouseButtonPressed(EcoSim::Input::MOUSE_SCROLL_DOWN))
        {
            float scroll = input->getMouseScrollValue(EcoSim::Input::MOUSE_SCROLL_UP) - input->getMouseScrollValue(EcoSim::Input::MOUSE_SCROLL_DOWN);
            cam->SetZoom(cam->GetTargetZoom() + scroll * ZOOM_SPEED);
        }

        graphics->update();
        graphics->render();
    }

    return 0;
}
