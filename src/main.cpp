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
#include <herbivore.hpp>
#include <carnivore.hpp>

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
    std::unique_ptr<EcoSim::TileMap> map = EcoSim::TileMapGenerator::generatePerlinNoiseMap(300, 200, graphics, 32);

    std::shared_ptr<EcoSim::EntityManager> entityManager = std::make_shared<EcoSim::EntityManager>(graphics, time);
    for (int i = 0; i < 10; i++)
    {
        entityManager->createEntity<EcoSim::Herbivore>(EcoSim::Vector2(i * 100 - 750, i * 50 - 500));
    }
    for (int i = 0; i < 3; i++)
    {
        entityManager->createEntity<EcoSim::Carnivore>(EcoSim::Vector2(i * 100 - 750, i * 50 - 500));
    }
    // std::shared_ptr<EcoSim::Carnivore> carnivore = entityManager->createEntity<EcoSim::Carnivore>(EcoSim::Vector2(400, -200));

    float SPEED = 100.0f;
    float ZOOM_SPEED = 0.2f;
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
        if (input->isKeyPressed(EcoSim::Input::KEY_R))
        {
            cam->SetZoom(1.0f);
        }
        if (input->isKeyPressed(EcoSim::Input::KEY_F))
        {
            cam->pos = EcoSim::Vector2(0, 0);
        }

        if (input->isKeyPressed(EcoSim::Input::KEY_SHIFT))
        {
            SPEED *= 2.0f;
        }
        if (input->isKeyPressed(EcoSim::Input::KEY_CTRL))
        {
            SPEED /= 2.0f;
        }

        graphics->update();
        graphics->render();
    }

    return 0;
}
