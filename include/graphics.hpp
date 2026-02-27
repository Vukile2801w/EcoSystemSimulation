#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "colors.hpp"
#include "math.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "time.hpp"

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
        void addUpdateCallback(const std::function<void()> &callback)
        {
            updateCallbacks.push_back(callback);
        }

        Vector2Int getScreenSize() const { return screenSize; }
        std::string getScreenTitle() const { return title; }

        virtual void render();
        virtual void update();
        virtual bool isRunning();

        virtual void drawTexture(Vector2 position, Texture &texture) = 0;

        std::shared_ptr<Camera> getCameraComponet() const
        {
            return cam;
        }
        std::shared_ptr<Time> getTimeComponet() const
        {
            return time;
        }

        Vector2 screenCenter() const
        {
            return Vector2(screenSize.x / 2.0f, screenSize.y / 2.0f);
        }

    protected:
        std::vector<std::function<void()>> drawCallbacks;
        std::vector<std::function<void()>> updateCallbacks;

        Vector2Int screenSize;
        std::string title;

        std::shared_ptr<EcoSim::Camera> cam;
        std::shared_ptr<EcoSim::Time> time;
    };
}

#endif
