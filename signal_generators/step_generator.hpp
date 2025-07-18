#pragma once

#include "../common/constants.hpp"

template <typename TimeType>
class StepGenerator {
private:
    float amplitude;
    TimeType stepTime;
    TimeType samplingTime;
    TimeType currentTime;

public:
    StepGenerator(float amplitude, TimeType stepTime, TimeType samplingTime)
        : amplitude(amplitude), stepTime(stepTime),
          samplingTime(samplingTime), currentTime(0) {}

    Point<TimeType> generateNext() {
        Point<TimeType> pt;
        pt.time = currentTime;
        pt.value = (currentTime >= stepTime) ? amplitude : 0.0f;
        currentTime += samplingTime;
        return pt;
    }

    Point<TimeType> getNthSample(int n) const {
        TimeType t = static_cast<TimeType>(n) * samplingTime;
        Point<TimeType> pt;
        pt.time = t;
        pt.value = (t >= stepTime) ? amplitude : 0.0f;
        return pt;
    }

    void reset() {
        currentTime = 0;
    }
};
