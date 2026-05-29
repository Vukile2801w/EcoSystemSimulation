#pragma once

#include <cmath>

class ValueNoise2D
{
private:
    static constexpr int MAX_PRIME_INDEX = 10;

    int numOctaves;
    int primeIndex;

    double persistence;

    int primes[MAX_PRIME_INDEX][3] = {
        {995615039, 600173719, 701464987},
        {831731269, 162318869, 136250887},
        {174329291, 946737083, 245679977},
        {362489573, 795918041, 350777237},
        {457025711, 880830799, 909678923},
        {787070341, 177340217, 593320781},
        {405493717, 291031019, 391950901},
        {458904767, 676625681, 424452397},
        {531736441, 939683957, 810651871},
        {997169939, 842027887, 423882827}};

private:
    double noise(int i, int x, int y) const
    {
        int n = x + y * 57;
        n = (n << 13) ^ n;

        int a = primes[i][0];
        int b = primes[i][1];
        int c = primes[i][2];

        int t = (n * (n * n * a + b) + c) & 0x7fffffff;

        return 1.0 - static_cast<double>(t) / 1073741824.0;
    }

    double smoothedNoise(int i, int x, int y) const
    {
        double corners =
            (noise(i, x - 1, y - 1) +
             noise(i, x + 1, y - 1) +
             noise(i, x - 1, y + 1) +
             noise(i, x + 1, y + 1)) /
            16.0;

        double sides =
            (noise(i, x - 1, y) +
             noise(i, x + 1, y) +
             noise(i, x, y - 1) +
             noise(i, x, y + 1)) /
            8.0;

        double center = noise(i, x, y) / 4.0;

        return corners + sides + center;
    }

    double interpolate(double a, double b, double x) const
    {
        double ft = x * 3.1415927;
        double f = (1.0 - std::cos(ft)) * 0.5;

        return a * (1.0 - f) + b * f;
    }

    double interpolatedNoise(int i, double x, double y) const
    {
        int integerX = static_cast<int>(x);
        double fractionalX = x - integerX;

        int integerY = static_cast<int>(y);
        double fractionalY = y - integerY;

        double v1 = smoothedNoise(i, integerX, integerY);
        double v2 = smoothedNoise(i, integerX + 1, integerY);
        double v3 = smoothedNoise(i, integerX, integerY + 1);
        double v4 = smoothedNoise(i, integerX + 1, integerY + 1);

        double i1 = interpolate(v1, v2, fractionalX);
        double i2 = interpolate(v3, v4, fractionalX);

        return interpolate(i1, i2, fractionalY);
    }

public:
    ValueNoise2D(
        int octaves = 7,
        double persistenceValue = 0.5,
        int primeIdx = 0)
        : numOctaves(octaves),
          primeIndex(primeIdx),
          persistence(persistenceValue)
    {
    }

    double generate(double x, double y) const
    {
        double total = 0.0;

        double frequency = 1.0;
        double amplitude = 1.0;

        double maxValue = 0.0;

        for (int i = 0; i < numOctaves; ++i)
        {
            total += interpolatedNoise(
                         (primeIndex + i) % MAX_PRIME_INDEX,
                         x * frequency,
                         y * frequency) *
                     amplitude;

            maxValue += amplitude;

            amplitude *= persistence;
            frequency *= 2.0;
        }

        total /= maxValue;

        // normalize from roughly [-0.5,0.5] -> [0,1]
        total = (total + 0.5) / 1.0;

        return std::clamp(total, 0.0, 1.0);
    }

    void setOctaves(int octaves)
    {
        numOctaves = octaves;
    }

    void setPersistence(double value)
    {
        persistence = value;
    }

    void setPrimeIndex(int index)
    {
        primeIndex = index % MAX_PRIME_INDEX;
    }
};