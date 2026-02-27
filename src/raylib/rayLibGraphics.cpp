#include <raylib/raylibGraphics.hpp>
#include <raylib/rayLibTexture.hpp>
#include <camera.hpp>
#include <iostream>
namespace EcoSim
{

    RaylibGraphics::RaylibGraphics(int width, int height, const std::string &title)
        : Graphics(width, height, title)
    {
        InitWindow(screenSize.x, screenSize.y, title.c_str());
        cam = std::make_shared<Camera>();
        time = std::make_shared<Time>();
    }

    RaylibGraphics::~RaylibGraphics()
    {
        CloseWindow();
    }

    void RaylibGraphics::render()
    {
        BeginDrawing();
        ClearBackground(toRaylibColor(backgroundColor));

        for (const auto &callback : drawCallbacks)
        {
            callback();
        }

        EndDrawing();
    }

    void RaylibGraphics::update()
    {
        time->Update();

        for (const auto &callback : updateCallbacks)
        {
            callback();
        }

        cam->Update(time->GetDeltaTime());
    }

    bool RaylibGraphics::isRunning()
    {
        return !WindowShouldClose();
    }

    void RaylibGraphics::drawTexture(Vector2 position, Texture &tex)
    {
        auto &rlTex = static_cast<RaylibTexture &>(tex);

        ::Vector2 transformed = {
            (position.x - cam->pos.x) * cam->GetZoom() + screenCenter().x,
            (position.y - cam->pos.y) * cam->GetZoom() + screenCenter().y};

        DrawTextureEx(
            rlTex.getNative(),
            transformed,
            0.0f,
            cam->GetZoom(),
            ::Color(255, 255, 255, 255));
    }

}
