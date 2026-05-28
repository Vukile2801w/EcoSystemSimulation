#ifndef MATH_HPP
#define MATH_HPP

#include <cstdint>
#include <cmath>
namespace EcoSim
{
    class Vector2;
    class Vector2Int;
    class Vector3;
    class Vector3Int;
    class Vector4;
    class Vector4Int;

    class Vector2
    {
    public:
        float x;
        float y;

        Vector2();
        Vector2(float x, float y);

        operator Vector2Int() const;
        operator Vector3Int() const;
        operator Vector4Int() const;
        operator Vector3() const;
        operator Vector4() const;

        bool operator==(const Vector2 &other) const;                              // Comparison operator
        bool operator!=(const Vector2 &other) const { return !(*this == other); } // Inequality operator

        Vector2 operator+(const Vector2 &other)
        {
            return Vector2(x + other.x, y + other.y);
        }

        Vector2 operator-(const Vector2 &other)
        {
            return Vector2(x - other.x, y - other.y);
        }

        Vector2 operator*(float scalar) const
        {
            return Vector2(x * scalar, y * scalar);
        }

        float dist(const Vector2 &other) const
        {
            float dx = x - other.x;
            float dy = y - other.y;
            return sqrt(dx * dx + dy * dy);
        }

        Vector2 normalize() const
        {
            float length = sqrt(x * x + y * y);
            if (length == 0)
                return Vector2(0, 0);
            return Vector2(x / length, y / length);
        }

        float length() const
        {
            return sqrt(x * x + y * y);
        }
    };

    class Vector2Int
    {
    public:
        int x;
        int y;

        Vector2Int();
        Vector2Int(int x, int y);

        operator Vector2() const;
        operator Vector3() const;
        operator Vector4() const;
        operator Vector3Int() const;
        operator Vector4Int() const;

        bool operator==(const Vector2Int &other) const;                              // Comparison operator
        bool operator!=(const Vector2Int &other) const { return !(*this == other); } // Inequality operator

        Vector2Int operator+(const Vector2Int &other)
        {
            return Vector2Int(x + other.x, y + other.y);
        }

        Vector2Int operator-(const Vector2Int &other)
        {
            return Vector2Int(x - other.x, y - other.y);
        }

        Vector2Int operator*(int scalar) const
        {
            return Vector2Int(x * scalar, y * scalar);
        }

        float dist(const Vector2Int &other) const
        {
            int dx = x - other.x;
            int dy = y - other.y;
            return sqrt(dx * dx + dy * dy);
        }

        Vector2Int normalize() const
        {
            float length = sqrt(x * x + y * y);
            if (length == 0)
                return Vector2Int(0, 0);
            return Vector2Int(static_cast<int>(x / length), static_cast<int>(y / length));
        }

        float length() const
        {
            return sqrt(x * x + y * y);
        }
    };

    class Vector3
    {
    public:
        float x;
        float y;
        float z;

        Vector3();
        Vector3(float x, float y, float z);

        operator Vector3Int() const;
        operator Vector4Int() const;
        operator Vector4() const;

        bool operator==(const Vector3 &other) const;                              // Comparison operator
        bool operator!=(const Vector3 &other) const { return !(*this == other); } // Inequality operator

        Vector3 operator+(const Vector3 &other)
        {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }

        Vector3 operator-(const Vector3 &other)
        {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }

        Vector3 operator*(float scalar) const
        {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }

        float dist(const Vector3 &other) const
        {
            float dx = x - other.x;
            float dy = y - other.y;
            float dz = z - other.z;
            return sqrt(dx * dx + dy * dy + dz * dz);
        }

        Vector3 normalize() const
        {
            float length = sqrt(x * x + y * y + z * z);
            if (length == 0)
                return Vector3(0, 0, 0);
            return Vector3(x / length, y / length, z / length);
        }

        float length() const
        {
            return sqrt(x * x + y * y + z * z);
        }
    };

    class Vector3Int
    {
    public:
        int x;
        int y;
        int z;

        Vector3Int();
        Vector3Int(int x, int y, int z);

        operator Vector3() const;
        operator Vector4() const;
        operator Vector4Int() const;

        bool operator==(const Vector3Int &other) const;                              // Comparison operator
        bool operator!=(const Vector3Int &other) const { return !(*this == other); } // Inequality operator

        Vector3Int operator+(const Vector3Int &other) const
        {
            return Vector3Int(x + other.x, y + other.y, z + other.z);
        }

        Vector3Int operator-(const Vector3Int &other) const
        {
            return Vector3Int(x - other.x, y - other.y, z - other.z);
        }

        Vector3Int operator*(int scalar) const
        {
            return Vector3Int(x * scalar, y * scalar, z * scalar);
        }

        float dist(const Vector3Int &other) const
        {
            int dx = x - other.x;
            int dy = y - other.y;
            int dz = z - other.z;
            return sqrt(dx * dx + dy * dy + dz * dz);
        }

        Vector3Int normalize() const
        {
            float length = sqrt(x * x + y * y + z * z);
            if (length == 0)
                return Vector3Int(0, 0, 0);
            return Vector3Int(static_cast<int>(x / length), static_cast<int>(y / length), static_cast<int>(z / length));
        }

        float length() const
        {
            return sqrt(x * x + y * y + z * z);
        }
    };

    class Vector4
    {
    public:
        float x;
        float y;
        float z;
        float w;

        Vector4();
        Vector4(float x, float y, float z, float w);

        operator Vector3() const;
        operator Vector4Int() const;

        bool operator==(const Vector4 &other) const;                              // Comparison operator
        bool operator!=(const Vector4 &other) const { return !(*this == other); } // Inequality operator

        Vector4 operator+(const Vector4 &other) const
        {
            return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
        }

        Vector4 operator-(const Vector4 &other) const
        {
            return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
        }

        Vector4 operator*(float scalar) const
        {
            return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
        }

        float dist(const Vector4 &other) const
        {
            float dx = x - other.x;
            float dy = y - other.y;
            float dz = z - other.z;
            float dw = w - other.w;
            return sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
        }

        Vector4 normalize() const
        {
            float length = sqrt(x * x + y * y + z * z + w * w);
            if (length == 0)
                return Vector4(0, 0, 0, 0);
            return Vector4(x / length, y / length, z / length, w / length);
        }

        float length() const
        {
            return sqrt(x * x + y * y + z * z + w * w);
        }
    };

    class Vector4Int
    {
    public:
        int x;
        int y;
        int z;
        int w;

        Vector4Int();
        Vector4Int(int x, int y, int z, int w);

        operator Vector3Int() const;
        operator Vector4() const;

        bool operator==(const Vector4Int &other) const;                              // Comparison operator
        bool operator!=(const Vector4Int &other) const { return !(*this == other); } // Inequality operator

        Vector4Int operator+(const Vector4Int &other) const
        {
            return Vector4Int(x + other.x, y + other.y, z + other.z, w + other.w);
        }
        Vector4Int operator-(const Vector4Int &other) const
        {
            return Vector4Int(x - other.x, y - other.y, z - other.z, w - other.w);
        }

        Vector4Int operator*(int scalar) const
        {
            return Vector4Int(x * scalar, y * scalar, z * scalar, w * scalar);
        }

        float dist(const Vector4Int &other) const
        {
            int dx = x - other.x;
            int dy = y - other.y;
            int dz = z - other.z;
            int dw = w - other.w;
            return sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
        }

        Vector4Int normalize() const
        {
            float length = sqrt(x * x + y * y + z * z + w * w);
            if (length == 0)
                return Vector4Int(0, 0, 0, 0);
            return Vector4Int(static_cast<int>(x / length), static_cast<int>(y / length), static_cast<int>(z / length), static_cast<int>(w / length));
        }
    };

    /**
     * @brief Clamps a value between a minimum and maximum value.
     * @param value The value to be clamped.
     * @param min The minimum value that the value should not be less than.
     * @param max The maximum value that the value should not be greater than.
     * @return The clamped value.
     *
     * This function returns the value if it is between the minimum and maximum values.
     * If the value is less than the minimum, the minimum value is returned.
     * If the value is greater than the maximum, the maximum value is returned.
     */
    float clamp(float value, float min, float max);

    /**
     * @brief Clamps an integer value between a minimum and maximum value.
     * @param value The value to be clamped.
     * @param min The minimum value that the value should not be less than.
     * @param max The maximum value that the value should not be greater than.
     * @return The clamped value.
     *
     * This function returns the value if it is between the minimum and maximum values.
     * If the value is less than the minimum, the minimum value is returned.
     * If the value is greater than the maximum, the maximum value is returned.
     **/
    int clamp(int value, int min, int max);

    int min(int a, int b);
    float min(float a, float b);

    int max(int a, int b);
    float max(float a, float b);

    float easeOutQuad(float t);
    float easeInOut(float t);

    float random(float min, float max);
    int random(int min, int max);
}

#endif
