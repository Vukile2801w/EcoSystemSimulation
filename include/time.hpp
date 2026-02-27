#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>

namespace EcoSim
{
    class Time
    {
    public:
        Time();

        float GetDeltaTime() const;
        float GetTotalTime() const;

        void Update();

    private:
        using clock = std::chrono::high_resolution_clock;

        std::chrono::time_point<clock> m_startTime;
        std::chrono::time_point<clock> m_endOfLastFrame;

        float m_deltaTime = 0.0f;
        float m_totalTime = 0.0f;
    };
}

#endif // TIME_HPP