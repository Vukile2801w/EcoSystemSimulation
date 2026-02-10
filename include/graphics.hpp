#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

// Standard includes
#include <string>
#include <vector>
#include <functional>

// External includes
#include <raylib.h>

// Internal includes
#include <math.hpp>
#include <colors.hpp>

namespace EcoSim
{
    class Graphics
    {
    public:
        Vector2Int screenSize;
        std::string title;
        Color backgroundColor = Color(255, 255, 255, 255);

        bool isRunning = true;

        Graphics();
        Graphics(int width, int height, const std::string &title = "Graphics Window");
        Graphics(const Vector2Int &size, const std::string &title = "Graphics Window");

        ~Graphics();

        void addDrawCallback(const std::function<void()> &callback)
        {
            drawCallbacks.push_back(callback);
        }

        void render();

    private:
        std::vector<std::function<void()>> drawCallbacks;
    };
};
#endif