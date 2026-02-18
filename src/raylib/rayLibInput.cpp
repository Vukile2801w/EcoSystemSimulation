#include <rayLibInput.hpp>
#include <raylib.h>

namespace EcoSim
{
    RayLibInput::RayLibInput()
    {
        for (int i = 1; i < RayLibInput::Key::KEY_COUNT; i++)
        {
            keyData[i] = KeyData{static_cast<Key>(i),
                                 false,
                                 false,
                                 false};
        }
    }

    RayLibInput::~RayLibInput() // Defined the destructor
    {
        // Optional cleanup logic can be placed here
    }

    void RayLibInput::handleInput()
    {
        // Manual mapping from EcoSim Keys to Raylib Keys
        for (int i = 1; i < Key::KEY_COUNT; i++)
        {
            Key key = static_cast<Key>(i);
            int raylibKey = -1; // Default invalid value

            switch (key)
            {
            case KEY_A:
                raylibKey = ::KEY_A;
                break;
            case KEY_B:
                raylibKey = ::KEY_B;
                break;
            case KEY_C:
                raylibKey = ::KEY_C;
                break;
            case KEY_D:
                raylibKey = ::KEY_D;
                break;
            case KEY_E:
                raylibKey = ::KEY_E;
                break;
            case KEY_F:
                raylibKey = ::KEY_F;
                break;
            case KEY_G:
                raylibKey = ::KEY_G;
                break;
            case KEY_H:
                raylibKey = ::KEY_H;
                break;
            case KEY_I:
                raylibKey = ::KEY_I;
                break;
            case KEY_J:
                raylibKey = ::KEY_J;
                break;
            case KEY_K:
                raylibKey = ::KEY_K;
                break;
            case KEY_L:
                raylibKey = ::KEY_L;
                break;
            case KEY_M:
                raylibKey = ::KEY_M;
                break;
            case KEY_N:
                raylibKey = ::KEY_N;
                break;
            case KEY_O:
                raylibKey = ::KEY_O;
                break;
            case KEY_P:
                raylibKey = ::KEY_P;
                break;
            case KEY_Q:
                raylibKey = ::KEY_Q;
                break;
            case KEY_R:
                raylibKey = ::KEY_R;
                break;
            case KEY_S:
                raylibKey = ::KEY_S;
                break;
            case KEY_T:
                raylibKey = ::KEY_T;
                break;
            case KEY_U:
                raylibKey = ::KEY_U;
                break;
            case KEY_V:
                raylibKey = ::KEY_V;
                break;
            case KEY_W:
                raylibKey = ::KEY_W;
                break;
            case KEY_X:
                raylibKey = ::KEY_X;
                break;
            case KEY_Y:
                raylibKey = ::KEY_Y;
                break;
            case KEY_Z:
                raylibKey = ::KEY_Z;
                break;
            case KEY_0:
                raylibKey = ::KEY_ZERO;
                break;
            case KEY_1:
                raylibKey = ::KEY_ONE;
                break;
            case KEY_2:
                raylibKey = ::KEY_TWO;
                break;
            case KEY_3:
                raylibKey = ::KEY_THREE;
                break;
            case KEY_4:
                raylibKey = ::KEY_FOUR;
                break;
            case KEY_5:
                raylibKey = ::KEY_FIVE;
                break;
            case KEY_6:
                raylibKey = ::KEY_SIX;
                break;
            case KEY_7:
                raylibKey = ::KEY_SEVEN;
                break;
            case KEY_8:
                raylibKey = ::KEY_EIGHT;
                break;
            case KEY_9:
                raylibKey = ::KEY_NINE;
                break;
            case KEY_SPACE:
                raylibKey = ::KEY_SPACE;
                break;
            case KEY_ENTER:
                raylibKey = ::KEY_ENTER;
                break;
            case KEY_TAB:
                raylibKey = ::KEY_TAB;
                break;
            case KEY_BACKSPACE:
                raylibKey = ::KEY_BACKSPACE;
                break;
            case KEY_DELETE:
                raylibKey = ::KEY_DELETE;
                break;
            case KEY_ESCAPE:
                raylibKey = ::KEY_ESCAPE;
                break;
            case KEY_SHIFT:
                raylibKey = ::KEY_LEFT_SHIFT;
                break;
            case KEY_CTRL:
                raylibKey = ::KEY_LEFT_CONTROL;
                break;
            case KEY_ALT:
                raylibKey = ::KEY_LEFT_ALT;
                break;
            case KEY_UP:
                raylibKey = ::KEY_UP;
                break;
            case KEY_DOWN:
                raylibKey = ::KEY_DOWN;
                break;
            case KEY_LEFT:
                raylibKey = ::KEY_LEFT;
                break;
            case KEY_RIGHT:
                raylibKey = ::KEY_RIGHT;
                break;
            case KEY_HOME:
                raylibKey = ::KEY_HOME;
                break;
            case KEY_END:
                raylibKey = ::KEY_END;
                break;
            case KEY_PAGE_UP:
                raylibKey = ::KEY_PAGE_UP;
                break;
            case KEY_PAGE_DOWN:
                raylibKey = ::KEY_PAGE_DOWN;
                break;
            case KEY_F1:
                raylibKey = ::KEY_F1;
                break;
            case KEY_F2:
                raylibKey = ::KEY_F2;
                break;
            case KEY_F3:
                raylibKey = ::KEY_F3;
                break;
            case KEY_F4:
                raylibKey = ::KEY_F4;
                break;
            case KEY_F5:
                raylibKey = ::KEY_F5;
                break;
            case KEY_F6:
                raylibKey = ::KEY_F6;
                break;
            case KEY_F7:
                raylibKey = ::KEY_F7;
                break;
            case KEY_F8:
                raylibKey = ::KEY_F8;
                break;
            case KEY_F9:
                raylibKey = ::KEY_F9;
                break;
            case KEY_F10:
                raylibKey = ::KEY_F10;
                break;
            case KEY_F11:
                raylibKey = ::KEY_F11;
                break;
            case KEY_F12:
                raylibKey = ::KEY_F12;
                break;
            default:
                continue; // Skip unrecognized keys
            }

            bool currentlyDown = IsKeyDown(raylibKey);

            keyData[i].isPressed = currentlyDown && !keyData[i].isDown;
            keyData[i].isReleased = !currentlyDown && keyData[i].isDown;
            keyData[i].isDown = currentlyDown;
        }
    }
}
