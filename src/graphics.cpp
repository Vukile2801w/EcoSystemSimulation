#include <graphics.hpp>
#include <raylib.h>

namespace EcoSim
{
    EcoSim::Graphics::Graphics(int width, int height, const std::string &title)
    {
        screenSize = Vector2Int(width, height);
        this->title = title;
    }

    Graphics::~Graphics() {}

    void Graphics::render()
    {
        // može biti prazno, čisto stub
    }

    bool Graphics::isRunning()
    {
        return true; // ili false, samo da linker ima definiciju
    }
}
