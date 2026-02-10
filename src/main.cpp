#include <memory>
#include <raylib/raylibGraphics.hpp>

int main()
{
    auto graphics = std::make_unique<EcoSim::RaylibGraphics>(800, 600, "My Window");
    graphics->backgroundColor = EcoSim::Color(100, 147, 249);

    while (graphics->isRunning())
    {
        graphics->render();
    }

    return 0;
}