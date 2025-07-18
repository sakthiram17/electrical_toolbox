#pragma once
#include <cmath>
#include "../common/constants.hpp"
#include "../common/signal.hpp"

template <typename TimeType>
class RampGenerator
{
private:
    float slope;
    TimeType samplingTime;
    TimeType currentTime;

public:
    RampGenerator(float slope, TimeType samplingTime)
        : slope(slope), samplingTime(samplingTime), currentTime(0.0f) {}

    Point<TimeType> generateNext()
    {
        Point<TimeType> pt;
        pt.time = currentTime;
        pt.value = slope * currentTime;
        currentTime += samplingTime;
        return pt;
    }

    Point<TimeType> getNthSample(int n) const
    {
        Point<TimeType> pt;
        pt.time = static_cast<TimeType>(n) * samplingTime;
        pt.value = slope * pt.time;
        return pt;
    }

    void reset()
    {
        currentTime = 0.0f;
    }

    void setSlope(float s) { slope = s; }
    void setSamplingTime(TimeType t) { samplingTime = t; }

    float getSlope() const { return slope; }
    TimeType getSamplingTime() const { return samplingTime; }
    TimeType getCurrentTime() const { return currentTime; }
};
