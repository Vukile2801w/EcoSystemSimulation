#ifndef MATH_HPP
#define MATH_HPP

#include <cstdint>

namespace EcoSim
{
    class Vector2
    {
    public:
        float x;
        float y;

        Vector2();
        Vector2(float x, float y);
    };
    class Vector2Int
    {
    public:
        int x;
        int y;

        Vector2Int();
        Vector2Int(int x, int y);
    };

    class Vector3
    {
    public:
        float x;
        float y;
        float z;

        Vector3();
        Vector3(float x, float y, float z);
    };
    class Vector3Int
    {
    public:
        int x;
        int y;
        int z;

        Vector3Int();
        Vector3Int(int x, int y, int z);
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
}
#endif