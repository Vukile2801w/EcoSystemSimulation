#include "math.hpp"
#include <cstdlib> // For rand() and RAND_MAX
namespace EcoSim
{

    // ===============================
    // Vector2
    // ===============================

    Vector2::Vector2() : x(0), y(0) {}
    Vector2::Vector2(float x, float y) : x(x), y(y) {}

    Vector2::operator Vector2Int() const
    {
        return Vector2Int(static_cast<int>(x), static_cast<int>(y));
    }

    Vector2::operator Vector3Int() const
    {
        return Vector3Int(static_cast<int>(x), static_cast<int>(y), 0);
    }

    Vector2::operator Vector4Int() const
    {
        return Vector4Int(static_cast<int>(x), static_cast<int>(y), 0, 0);
    }

    Vector2::operator Vector3() const
    {
        return Vector3(x, y, 0.0f);
    }

    Vector2::operator Vector4() const
    {
        return Vector4(x, y, 0.0f, 0.0f);
    }

    bool Vector2::operator==(const Vector2 &other) const
    {
        return (x == other.x) && (y == other.y);
    }

    // ===============================
    // Vector2Int
    // ===============================

    Vector2Int::Vector2Int() : x(0), y(0) {}
    Vector2Int::Vector2Int(int x, int y) : x(x), y(y) {}

    Vector2Int::operator Vector2() const
    {
        return Vector2(static_cast<float>(x), static_cast<float>(y));
    }

    Vector2Int::operator Vector3() const
    {
        return Vector3(static_cast<float>(x), static_cast<float>(y), 0.0f);
    }

    Vector2Int::operator Vector4() const
    {
        return Vector4(static_cast<float>(x), static_cast<float>(y), 0.0f, 0.0f);
    }

    Vector2Int::operator Vector3Int() const
    {
        return Vector3Int(x, y, 0);
    }

    Vector2Int::operator Vector4Int() const
    {
        return Vector4Int(x, y, 0, 0);
    }

    bool Vector2Int::operator==(const Vector2Int &other) const
    {
        return (x == other.x) && (y == other.y);
    }

    // ===============================
    // Vector3
    // ===============================

    Vector3::Vector3() : x(0), y(0), z(0) {}
    Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3::operator Vector3Int() const
    {
        return Vector3Int(static_cast<int>(x), static_cast<int>(y), static_cast<int>(z));
    }

    Vector3::operator Vector4Int() const
    {
        return Vector4Int(static_cast<int>(x), static_cast<int>(y), static_cast<int>(z), 0);
    }

    Vector3::operator Vector4() const
    {
        return Vector4(x, y, z, 0.0f);
    }

    bool Vector3::operator==(const Vector3 &other) const
    {
        return (x == other.x) && (y == other.y) && (z == other.z);
    }

    // ===============================
    // Vector3Int
    // ===============================

    Vector3Int::Vector3Int() : x(0), y(0), z(0) {}
    Vector3Int::Vector3Int(int x, int y, int z) : x(x), y(y), z(z) {}

    Vector3Int::operator Vector3() const
    {
        return Vector3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
    }

    Vector3Int::operator Vector4() const
    {
        return Vector4(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), 0.0f);
    }

    Vector3Int::operator Vector4Int() const
    {
        return Vector4Int(x, y, z, 0);
    }

    bool Vector3Int::operator==(const Vector3Int &other) const
    {
        return (x == other.x) && (y == other.y) && (z == other.z);
    }

    // ===============================
    // Vector4
    // ===============================

    Vector4::Vector4() : x(0), y(0), z(0), w(0) {}
    Vector4::Vector4(float x, float y, float z, float w)
        : x(x), y(y), z(z), w(w) {}

    Vector4::operator Vector3() const
    {
        return Vector3(x, y, z);
    }

    Vector4::operator Vector4Int() const
    {
        return Vector4Int(
            static_cast<int>(x),
            static_cast<int>(y),
            static_cast<int>(z),
            static_cast<int>(w));
    }

    bool Vector4::operator==(const Vector4 &other) const
    {
        return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
    }

    // ===============================
    // Vector4Int
    // ===============================

    Vector4Int::Vector4Int() : x(0), y(0), z(0), w(0) {}
    Vector4Int::Vector4Int(int x, int y, int z, int w)
        : x(x), y(y), z(z), w(w) {}

    Vector4Int::operator Vector3Int() const
    {
        return Vector3Int(x, y, z);
    }

    Vector4Int::operator Vector4() const
    {
        return Vector4(
            static_cast<float>(x),
            static_cast<float>(y),
            static_cast<float>(z),
            static_cast<float>(w));
    }

    bool Vector4Int::operator==(const Vector4Int &other) const
    {
        return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
    }

    // ===============================
    // Clamp
    // ===============================

    float clamp(float value, float min, float max)
    {
        if (value < min)
            return min;
        if (value > max)
            return max;
        return value;
    }

    int clamp(int value, int min, int max)
    {
        if (value < min)
            return min;
        if (value > max)
            return max;
        return value;
    }

    int min(int a, int b)
    {
        return (a < b) ? a : b;
    }
    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    float min(float a, float b)
    {
        return (a < b) ? a : b;
    }
    float max(float a, float b)
    {
        return (a > b) ? a : b;
    }

    float easeOutQuad(float t)
    {
        return 1.0f - (1.0f - t) * (1.0f - t);
    }
    float easeInOut(float x)
    {
        x = clamp(x, 0.0f, 1.0f);

        float k = 5.0f;

        float a = 1.0f / (1.0f + std::exp(-k * (x - 0.5f)));
        float min = 1.0f / (1.0f + std::exp(k * 0.5f));
        float max = 1.0f / (1.0f + std::exp(-k * 0.5f));

        return (a - min) / (max - min);
    }

    float random(float min, float max)
    {
        return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
    }
    int random(int min, int max)
    {
        return min + rand() % (max - min + 1);
    }

} // namespace EcoSim
