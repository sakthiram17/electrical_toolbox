#pragma once

#include "../common/constants.hpp"
#include "../common/signal.hpp"
#include <cmath>

template <typename TimeType>
class SineGenerator {
private:
    float frequency;
    float amplitude;
    float phase;
    TimeType samplingTime;
    TimeType currentTime;

public:
    SineGenerator(float frequency, float amplitude, float phase, TimeType samplingTime)
        : frequency(frequency),
          amplitude(amplitude),
          phase(phase),
          samplingTime(samplingTime),
          currentTime(0.0f) {}

    Point<TimeType> generateNext() {
        Point<TimeType> pt;
        pt.time = currentTime;
        pt.value = amplitude * std::sinf(2.0f * PI * frequency * static_cast<float>(currentTime) + phase);
        currentTime += samplingTime;
        return pt;
    }

    Point<TimeType> generateNthSample(std::size_t n) const {
        TimeType t = static_cast<TimeType>(n) * samplingTime;
        Point<TimeType> pt;
        pt.time = t;
        pt.value = amplitude * std::sinf(2.0f * PI * frequency * static_cast<float>(t) + phase);
        return pt;
    }

    void reset() {
        currentTime = 0.0f;
    }
    
    void setFrequency(float f) { frequency = f; }
    void setAmplitude(float a) { amplitude = a; }
    void setPhase(float p) { phase = p; }
    void setSamplingTime(TimeType t) { samplingTime = t; }

    float getFrequency() const { return frequency; }
    float getAmplitude() const { return amplitude; }
    float getPhase() const { return phase; }
    TimeType getSamplingTime() const { return samplingTime; }
    TimeType getCurrentTime() const { return currentTime; }
};
