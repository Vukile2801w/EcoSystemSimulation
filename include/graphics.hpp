#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "colors.hpp"
#include "math.hpp"

namespace EcoSim
{
    class Graphics
    {
    public:
        Vector2Int screenSize;
        std::string title;
        Color backgroundColor = Color(255, 255, 255, 255);

        Graphics() : Graphics(800, 600, "Graphics Window") {};
        Graphics(int width, int height, const std::string &title = "Graphics Window");
        virtual ~Graphics();

        void addDrawCallback(const std::function<void()> &callback)
        {
            drawCallbacks.push_back(callback);
        }

        virtual void render();
        virtual bool isRunning();

    protected:
        std::vector<std::function<void()>> drawCallbacks;
    };
}

#endif
