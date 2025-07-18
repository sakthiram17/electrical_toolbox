#pragma once

#include "../common/constants.hpp"
#include "../common/signal.hpp"
#include <cmath>

template <typename TimeType>
class ExponentialGenerator
{
private:
    float amplitude;
    float tau;
    TimeType samplingTime;
    TimeType currentTime;

public:
    ExponentialGenerator(float amplitude, float tau, TimeType samplingTime)
        : amplitude(amplitude), tau(tau), samplingTime(samplingTime), currentTime(0.0f) {}

    Point<TimeType> generateNext()
    {
        Point<TimeType> pt;
        pt.time = currentTime;
        pt.value = amplitude * std::exp(-currentTime / tau);
        currentTime += samplingTime;
        return pt;
    }

    Point<TimeType> generateNthSample(int n) const
    {
        Point<TimeType> pt;
        pt.time = static_cast<TimeType>(n) * samplingTime;
        pt.value = amplitude * std::exp(-pt.time / tau);
        return pt;
    }

    void reset()
    {
        currentTime = 0.0f;
    }

    void setAmplitude(float a) { amplitude = a; }
    void setTau(float t) { tau = t; }
    void setSamplingTime(TimeType t) { samplingTime = t; }

    float getAmplitude() const { return amplitude; }
    float getTau() const { return tau; }
    TimeType getSamplingTime() const { return samplingTime; }
    TimeType getCurrentTime() const { return currentTime; }
};
