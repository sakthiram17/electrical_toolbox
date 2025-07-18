#pragma once
#include "../common/constants.hpp"
#include "../common/signal.hpp"
#include <cmath>

template <typename TimeType>
class TriangleGenerator
{
private:
    float amplitude;
    TimeType period;
    TimeType samplingTime;
    TimeType currentTime;

public:
    TriangleGenerator(float amplitude, TimeType period, TimeType samplingTime)
        : amplitude(amplitude), period(period),
          samplingTime(samplingTime), currentTime(0) {}

    Point<TimeType> generateNext()
    {
        Point<TimeType> pt;
        pt.time = currentTime;

        TimeType t_mod = fmod(currentTime, period);
        float slope = (4.0f * amplitude) / static_cast<float>(period);

        if (t_mod < period / static_cast<TimeType>(2.0f))
        {
            pt.value = slope * static_cast<float>(t_mod) - amplitude;
        }
        else
        {
            pt.value = -slope * static_cast<float>(t_mod - period / 2) + amplitude;
        }

        currentTime += samplingTime;
        return pt;
    }

    Point<TimeType> getNthSample(int n) const
    {
        TimeType t = static_cast<TimeType>(n) * samplingTime;
        Point<TimeType> pt;
        pt.time = t;

        TimeType t_mod = fmod(t, period);
        float slope = (4.0f * amplitude) / static_cast<float>(period);

        if (t_mod < period / static_cast<TimeType>(2.0f))
        {
            pt.value = slope * static_cast<float>(t_mod) - amplitude;
        }
        else
        {
            pt.value = -slope * static_cast<float>(t_mod - period / 2) + amplitude;
        }

        return pt;
    }

    void reset()
    {
        currentTime = 0;
    }
};
