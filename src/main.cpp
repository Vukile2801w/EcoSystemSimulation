#include <memory>
#include <raylibGraphics.hpp>
#include <rayLibTexture.hpp>
#include <math.hpp>
#include <iostream>

int main()
{
    auto graphics = std::make_shared<EcoSim::RaylibGraphics>(800, 600, "My Window");
    graphics->backgroundColor = EcoSim::Color(100, 147, 249);

    EcoSim::RaylibTexture tex("../assets/logo.jpg");
    if (!tex.isTextureLoaded())
        return -1;

    int x = 0, y = 0; // Initialize both x and y
    int i = 1, k = 1;

    // Using lambda function for draw callback
    graphics->addDrawCallback([&]()
                              {
        graphics->drawTexture(EcoSim::Vector2Int(x, y), tex);
        x += i;
        y += k;
        if (x > 800-tex.getWidth()) // Changed to check both x and y
            i *= -1; 
        if (y > 600-tex.getWidth())
            k *= -1;
        if (x < 0) // Check if either is less than 0
            i *= -1;
        if (y < 0)
            k *= -1; });

    while (graphics->isRunning())
    {
        graphics->render();
    }

    return 0;
}
