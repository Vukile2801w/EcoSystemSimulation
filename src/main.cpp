#include <memory>
#include <raylib.h>
#include <engine.hpp>

int main()
{
    auto graphics = std::make_unique<EcoSim::Graphics>();
    graphics->backgroundColor = EcoSim::Color(100, 147, 249);

    EcoSim::Texture backGround = EcoSim::Texture("assets/background.png");

    graphics->addDrawCallback([&]()
                              { DrawTexture(backGround.getNative(), 0, 0, WHITE); });

    while (!WindowShouldClose())
    {
        graphics->render();
    }

    return 0;
}