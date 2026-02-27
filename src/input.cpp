#include "input.hpp"

namespace EcoSim
{
    // ================================== //
    //      Keyboard Button Functions     //
    // ================================== //

    bool Input::isKeyDown(Key key)
    {
        if (key <= Key::KEY_UNKNOWN || key >= Key::KEY_COUNT)
            return false;

        return keyData[key].isDown;
    }

    bool Input::isKeyPressed(Key key)
    {
        if (key <= Key::KEY_UNKNOWN || key >= Key::KEY_COUNT)
            return false;

        return keyData[key].isPressed;
    }

    bool Input::isKeyReleased(Key key)
    {
        if (key <= Key::KEY_UNKNOWN || key >= Key::KEY_COUNT)
            return false;

        return keyData[key].isReleased;
    }

    // =============================== //
    //      Mouse Button Functions     //
    // =============================== //

    bool Input::isMouseButtonDown(MouseButton key)
    {
        if (key <= MouseButton::MOUSE_BUTTON_UNKNOWN || key >= MouseButton::MOUSE_BUTTON_COUNT)
            return false;

        return mouseButtonData[static_cast<size_t>(key)].value > 0.0f ? true : false;
    }

    bool Input::isMouseButtonPressed(MouseButton key)
    {
        if (key <= MouseButton::MOUSE_BUTTON_UNKNOWN || key >= MouseButton::MOUSE_BUTTON_COUNT)
            return false;

        return mouseButtonData[static_cast<size_t>(key)].isPressed;
    }

    bool Input::isMouseButtonReleased(MouseButton key)
    {
        if (key <= MouseButton::MOUSE_BUTTON_UNKNOWN || key >= MouseButton::MOUSE_BUTTON_COUNT)
            return false;

        return mouseButtonData[static_cast<size_t>(key)].isReleased;
    }

    float Input::getMouseScrollValue(MouseButton key)
    {
        if (key != MouseButton::MOUSE_SCROLL_UP && key != MouseButton::MOUSE_SCROLL_DOWN)
            return 0.0f;

        return mouseButtonData[static_cast<size_t>(key)].value;
    }
}
