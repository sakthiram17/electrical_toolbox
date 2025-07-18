#pragma once

#include <cmath>
#include "../common/constants.hpp"
#include "../common/signal.hpp"

template <typename TimeType>
class RectWaveGenerator {
private:
    float frequency;
    float phase;
    float samplingTime;
    float dutyCycle;
    float highValue;
    float lowValue;
    TimeType currentTime;

public:
    RectWaveGenerator(float frequency, float phase, float samplingTime,
                      float dutyCycle, float highValue, float lowValue)
        : frequency(frequency), phase(phase), samplingTime(samplingTime),
          dutyCycle(dutyCycle), highValue(highValue), lowValue(lowValue),
          currentTime(0.0f) {}

    Point<TimeType> generateNext() {
        Point<TimeType> pt;
        pt.time = currentTime;

        float period = 1.0f / frequency;
        float onTime = dutyCycle * period;

        float t_shifted = currentTime + phase / (2.0f * PI * frequency);
        float t_in_period = fmodf(t_shifted, period);

        pt.value = (t_in_period < onTime) ? highValue : lowValue;

        currentTime += samplingTime;
        return pt;
    }

    Point<TimeType> getNthSample(int n) const {
        Point<TimeType> pt;
        pt.time = static_cast<TimeType>(n) * samplingTime;

        float period = 1.0f / frequency;
        float onTime = dutyCycle * period;

        float t_shifted = pt.time + phase / (2.0f * PI * frequency);
        float t_in_period = fmodf(t_shifted, period);

        pt.value = (t_in_period < onTime) ? highValue : lowValue;
        return pt;
    }

    void reset() {
        currentTime = 0.0f;
    }

    // Setters
    void setFrequency(float f) { frequency = f; }
    void setPhase(float p) { phase = p; }
    void setDutyCycle(float d) { dutyCycle = d; }
    void setSamplingTime(float t) { samplingTime = t; }
    void setHighValue(float h) { highValue = h; }
    void setLowValue(float l) { lowValue = l; }

    // Getters
    float getFrequency() const { return frequency; }
    float getPhase() const { return phase; }
    float getDutyCycle() const { return dutyCycle; }
    float getSamplingTime() const { return samplingTime; }
    float getHighValue() const { return highValue; }
    float getLowValue() const { return lowValue; }
    TimeType getCurrentTime() const { return currentTime; }
};
