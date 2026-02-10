#include "math.hpp"

namespace EcoSim
{

    Vector2Int::Vector2Int() : x(0), y(0) {}
    Vector2Int::Vector2Int(int x, int y) : x(x), y(y) {}

    Vector2::Vector2() : x(0), y(0) {}
    Vector2::Vector2(float x, float y) : x(x), y(y) {}

    Vector3Int::Vector3Int() : x(0), y(0), z(0) {}
    Vector3Int::Vector3Int(int x, int y, int z) : x(x), y(y), z(z) {}

    Vector3::Vector3() : x(0), y(0), z(0) {}
    Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector4Int::Vector4Int() : x(0), y(0), z(0), w(0) {}
    Vector4Int::Vector4Int(int x, int y, int z, int w) : x(x), y(y), z(z), w(w) {}

    Vector4::Vector4() : x(0), y(0), z(0), w(0) {}
    Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

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

} // namespace EcoSim
