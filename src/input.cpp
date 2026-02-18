#include "input.hpp"

namespace EcoSim
{
    bool Input::isKeyDown(Input::Key key)
    {
        if (key <= Key::KEY_UNKNOWN || key >= Key::KEY_COUNT)
            return false;

        return keyData[key].isDown;
    }

    bool Input::isKeyPressed(Input::Key key)
    {
        if (key <= Key::KEY_UNKNOWN || key >= Key::KEY_COUNT)
            return false;

        return keyData[key].isPressed;
    }

    bool Input::isKeyReleased(Input::Key key)
    {
        if (key <= Key::KEY_UNKNOWN || key >= Key::KEY_COUNT)
            return false;

        return keyData[key].isReleased;
    }
}
