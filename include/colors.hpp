#ifndef COLORS_HPP
#define COLORS_HPP

#include <math.hpp>
#include <raylib.h>

namespace EcoSim
{
    struct Color
    {
    public:
        uint8_t r; // Red component (0-255)
        uint8_t g; // Green component (0-255)
        uint8_t b; // Blue component (0-255)
        uint8_t a; // Alpha component (0-255, where 0 is fully transparent and 255 is fully opaque)

        Color() : r(255), g(0), b(255), a(255) {}

        /// @brief
        /// Constructor for Color class using a 32-bit hexadecimal code.
        ///
        /// @param hex A 32-bit hexadecimal code representing the color.
        ///
        /// If the hexadecimal code is in the format 0xAARRGGB, the alpha component is set to the value of AA.
        /// If the hexadecimal code is in the format 0xRRGGBB, the alpha component is set to 255 (fully opaque).
        ///
        /// The red component is set to the value of RR, the green component is set to the value of GG, and the blue component is set to the value of BB.
        ///
        /// The color components are clamped to the range [0, 255] to ensure they are within the valid range for the color class.
        Color(uint32_t hex)
        {
            a = hex & 0xFF000000 ? (hex >> 24) & 0xFF : 255; // Check if alpha is provided
            r = (hex >> 16) & 0xFF;
            g = (hex >> 8) & 0xFF;
            b = hex & 0xFF;
            m_clampColor();
        }
        /// @brief
        /// Constructor for Color class.
        ///
        /// @param r Red component (0-255)
        /// @param g Green component (0-255)
        /// @param b Blue component (0-255)
        /// @param a Alpha component (0-255, where 0 is fully transparent and 255 is fully opaque)
        ///
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
            m_clampColor();
        }
        /// @brief
        /// Constructor for Color class, taking a Vector4Int as argument.
        ///
        /// The components of the Vector4Int are interpreted as follows:
        /// x = Red component (0-255)
        /// y = Green component (0-255)
        /// z = Blue component (0-255)
        /// w = Alpha component (0-255, where 0 is fully transparent and 255 is fully opaque)
        ///
        /// The color components are clamped to ensure they are within the valid range.
        Color(Vector4Int color)
        {
            r = color.x;
            g = color.y;
            b = color.z;
            a = color.w;
            m_clampColor();
        }

        /// @brief
        /// Constructor for Color class, taking a Vector3Int as argument.
        ///
        /// The components of the Vector3Int are interpreted as follows:
        /// x = Red component (0-255)
        /// y = Green component (0-255)
        /// z = Blue component (0-255)
        ///
        /// The color components are clamped to ensure they are within the valid range.
        /// The alpha component is set to 255 (fully opaque) by default.

        Color(Vector3Int color)
        {
            r = color.x;
            g = color.y;
            b = color.z;
            a = 255;
            m_clampColor();
        }

    private:
        /// @brief
        /// Clamps the color components to the range [0, 255].
        /// This is a private helper function that is called by the constructors
        /// and setters to ensure that the color components are always within
        /// the valid range.
        void m_clampColor()
        {
            r = clamp(r, 0, 255);
            g = clamp(g, 0, 255);
            b = clamp(b, 0, 255);
            a = clamp(a, 0, 255);
        }
    };
};
#endif