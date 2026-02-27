#include <memory>
#include <iostream>

#include <rayLibGraphics.hpp>
#include <rayLibTexture.hpp>
#include <math.hpp>
#include <tilemap.hpp>
#include <rayLibInput.hpp>
#include <time.hpp>

int main()
{

    auto graphics = std::make_shared<EcoSim::RaylibGraphics>(800, 600, "My Window");
    graphics->backgroundColor = EcoSim::Color(36, 36, 35);

    auto cam = graphics->getCameraComponet();
    auto time = graphics->getTimeComponet();

    auto input = std::make_shared<EcoSim::RayLibInput>();

    std::vector<std::shared_ptr<EcoSim::RaylibTexture>> textures = EcoSim::RaylibTexture::loadTextureAtlas("C:/Users/User/Desktop/vuk/programiranje/c++/EcoSystemSimulation/build/assets/tilemap.png", {32, 32});
    for (int i = 0; i < textures.size(); i++)
    {
        EcoSim::TileDefinition tile = EcoSim::TileDefinition();
        tile.texture = textures[i];
        EcoSim::TileID tileID = EcoSim::TileRegistry::registerTile(tile);
        std::cout
            << " Registered tile " << i << " with ID: " << tileID << std::endl;
    }

    EcoSim::TileMap *map = new EcoSim::TileMap(25, 19, graphics, 32);
    map->loadTileMap("C:/Users/User/Desktop/vuk/programiranje/c++/EcoSystemSimulation/build/assets/TileMap/map.tmx");

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

            std::cout << "Mouse Scroll Button: {name: " << EcoSim::Input::MOUSE_SCROLL_UP << ", isDown: " << input->isMouseButtonDown(EcoSim::Input::MOUSE_SCROLL_UP) << ", isPressed: " << input->isMouseButtonPressed(EcoSim::Input::MOUSE_SCROLL_UP) << ", isReleased: " << input->isMouseButtonReleased(EcoSim::Input::MOUSE_SCROLL_UP) << ", value: " << input->getMouseScrollValue(EcoSim::Input::MOUSE_SCROLL_UP) << "}" << std::endl;

            std::cout << "Mouse Scroll Button: {name: " << EcoSim::Input::MOUSE_SCROLL_DOWN << ", isDown: " << input->isMouseButtonDown(EcoSim::Input::MOUSE_SCROLL_DOWN) << ", isPressed: " << input->isMouseButtonPressed(EcoSim::Input::MOUSE_SCROLL_DOWN) << ", isReleased: " << input->isMouseButtonReleased(EcoSim::Input::MOUSE_SCROLL_DOWN) << ", value: " << input->getMouseScrollValue(EcoSim::Input::MOUSE_SCROLL_DOWN) << "}" << std::endl;
        }

        graphics->update();

        graphics->render();
    }

    return 0;
}
