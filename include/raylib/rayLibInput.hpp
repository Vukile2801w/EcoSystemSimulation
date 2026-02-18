#ifndef RAYLIBINPUT_HPP
#define RAYLIBINPUT_HPP

#include <input.hpp>

namespace EcoSim
{
    class RayLibInput : public Input
    {
    public:
        RayLibInput();
        ~RayLibInput();

        void handleInput() override;

    private:
    };
}
#endif // RAYLIBINPUT_HPP