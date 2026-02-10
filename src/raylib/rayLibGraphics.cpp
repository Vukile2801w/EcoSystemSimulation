#include <raylib/raylibGraphics.hpp>

namespace EcoSim
{

    EcoSim::RaylibGraphics::RaylibGraphics(int width, int height, const std::string &title)
        : Graphics(width, height, title)
    {
        InitWindow(screenSize.x, screenSize.y, title.c_str());
    }

    EcoSim::RaylibGraphics::~RaylibGraphics()
    {
        CloseWindow();
    }

    void EcoSim::RaylibGraphics::render()
    {
        BeginDrawing();
        ClearBackground(toRaylibColor(backgroundColor));

        for (const auto &callback : drawCallbacks)
        {
            callback();
        }

        EndDrawing();
    }

    bool EcoSim::RaylibGraphics::isRunning()
    {
        return !WindowShouldClose();
    }

}
