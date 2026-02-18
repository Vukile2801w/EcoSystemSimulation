#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "colors.hpp"
#include "math.hpp"
#include "texture.hpp"

namespace EcoSim
{
    class Graphics
    {
    public:
        Color backgroundColor = Color(255, 255, 255, 255);

        Graphics() : Graphics(800, 600, "Graphics Window") {};
        Graphics(int width, int height, const std::string &title = "Graphics Window");
        virtual ~Graphics();

        void addDrawCallback(const std::function<void()> &callback)
        {
            drawCallbacks.push_back(callback);
        }

        Vector2Int getScreenSize() const { return screenSize; }
        std::string getScreenTitle() const { return title; }

        virtual void render();
        virtual bool isRunning();

        virtual void drawTexture(Vector2 position, Texture &texture) = 0;

    protected:
        std::vector<std::function<void()>> drawCallbacks;

        Vector2Int screenSize;
        std::string title;
    };
}

#endif
