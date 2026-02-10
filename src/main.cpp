#include <memory>
#include <raylib.h>
#include <graphics.hpp>
int main()
{
    auto graphics = std::make_unique<EcoSim::Graphics>();
    graphics->backgroundColor = EcoSim::Color(100, 147, 249);

    while (!WindowShouldClose())
    {
        graphics->render();
    }

    return 0;
}