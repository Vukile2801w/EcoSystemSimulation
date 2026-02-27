#include "Time.hpp"

namespace EcoSim
{
    Time::Time()
    {
        m_startTime = clock::now();
        m_endOfLastFrame = m_startTime;
    }

    void Time::Update()
    {
        auto now = clock::now();

        std::chrono::duration<float> delta = now - m_endOfLastFrame;
        m_deltaTime = delta.count();

        std::chrono::duration<float> total = now - m_startTime;
        m_totalTime = total.count();

        m_endOfLastFrame = now;
    }

    float Time::GetDeltaTime() const
    {
        return m_deltaTime;
    }

    float Time::GetTotalTime() const
    {
        return m_totalTime;
    }
}