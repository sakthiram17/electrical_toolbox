#pragma once

#include <cmath>
#include "../common/constants.hpp"
#include "../common/signal.hpp"


template <typename TimeType>
class SawtoothGenerator {
private:
    float amplitude;
    float period;
    TimeType samplingTime;
    TimeType currentTime;

public:
    SawtoothGenerator(float amplitude, float period, TimeType samplingTime)
        : amplitude(amplitude), period(period), samplingTime(samplingTime), currentTime(0.0f) {}

    Point<TimeType> generateNext() {
        Point<TimeType> pt;
        pt.time = currentTime;
        float t_mod = std::fmod(static_cast<float>(currentTime), period);
        pt.value = (2.0f * amplitude / period) * t_mod - amplitude;
        currentTime += samplingTime;
        return pt;
    }

    Point<TimeType> getNthSample(std::size_t n) const {
        TimeType t = static_cast<TimeType>(n) * samplingTime;
        Point<TimeType> pt;
        pt.time = t;
        float t_mod = std::fmod(static_cast<float>(t), period);
        pt.value = (2.0f * amplitude / period) * t_mod - amplitude;
        return pt;
    }

    void reset() {
        currentTime = 0.0f;
    }

    // Optional setters and getters
    void setAmplitude(float a) { amplitude = a; }
    void setPeriod(float p) { period = p; }
    void setSamplingTime(TimeType t) { samplingTime = t; }

    float getAmplitude() const { return amplitude; }
    float getPeriod() const { return period; }
    TimeType getSamplingTime() const { return samplingTime; }
    TimeType getCurrentTime() const { return currentTime; }
};