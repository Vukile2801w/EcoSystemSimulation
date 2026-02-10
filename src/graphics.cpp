#include <graphics.hpp>

EcoSim::Graphics::Graphics()
{
    screenSize = Vector2Int(800, 600);
    title = "Graphics Window";
    InitWindow(screenSize.x, screenSize.y, title.c_str());
}

EcoSim::Graphics::Graphics(int width, int height, const std::string &title)
{
    screenSize = Vector2Int(width, height);
    this->title = title;
    InitWindow(screenSize.x, screenSize.y, title.c_str());
}

EcoSim::Graphics::Graphics(const Vector2Int &size, const std::string &title)
{
    screenSize = size;
    this->title = title;
    InitWindow(screenSize.x, screenSize.y, title.c_str());
}

EcoSim::Graphics::~Graphics()
{
    CloseWindow();
}

void EcoSim::Graphics::render()
{
    BeginDrawing();
    ClearBackground(backgroundColor);

    for (const auto &callback : drawCallbacks)
    {
        callback();
    }

    EndDrawing();

    isRunning = !WindowShouldClose(); // Update isRunning based on window state
}