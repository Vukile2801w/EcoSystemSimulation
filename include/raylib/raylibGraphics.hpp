#ifndef RAYLIB_GRAPHICS_HPP
#define RAYLIB_GRAPHICS_HPP

#include <graphics.hpp>
#include <colors.hpp>

namespace EcoSim
{
    class RaylibGraphics : public Graphics
    {
    public:
        RaylibGraphics() = delete;
        RaylibGraphics(int width, int height, const std::string &title = "Graphics Window");
        ~RaylibGraphics();

        void render() override;
        void update() override;
        bool isRunning() override;

        void drawTexture(Vector2 position, Texture &texture) override;
        void drawCircle(Vector2 position, float radius, Color color);
        void drawRectangle(Vector2 position, Vector2 size, Color color);
    
        static ::Color toRaylibColor(const Color &c)
        {
            return ::Color{c.r, c.g, c.b, c.a}; // Raylib Color
        }
        protected:
    };
}

#endif