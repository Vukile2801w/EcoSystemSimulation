#include <raylib/raylibGraphics.hpp>
#include <raylib/rayLibTexture.hpp>

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

    void RaylibGraphics::drawTexture(Vector2 position, Texture &tex)
    {
        auto &rlTex = static_cast<RaylibTexture &>(tex);
        DrawTexture(rlTex.getNative(), position.x, position.y, toRaylibColor(Color(0xFFFFFF)));
    }

}
