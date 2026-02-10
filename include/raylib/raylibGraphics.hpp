#ifndef RAYLIB_GRAPHICS_HPP
#define RAYLIB_GRAPHICS_HPP

#include <graphics.hpp>
#include <colors.hpp>

namespace EcoSim
{
    class RaylibGraphics : public Graphics
    {
    public:
        RaylibGraphics() {}
        RaylibGraphics(int width, int height, const std::string &title = "Graphics Window");
        ~RaylibGraphics();

        void render() override;
        bool isRunning() override;

    protected:
        ::Color toRaylibColor(const Color &c) const
        {
            return ::Color{c.r, c.g, c.b, c.a}; // Raylib Color
        }
    };
}

#endif