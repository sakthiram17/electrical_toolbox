#include "delta_generator.hpp"
#include "../common/signal.hpp"

DeltaGenerator::DeltaGenerator(float amplitude, float impulseTime, float samplingTime)
    : amplitude(amplitude), impulseTime(impulseTime),
      samplingTime(samplingTime), currentTime(0.0f) {}

Point<float> DeltaGenerator::generateNext() {
    Point<float> pt;
    pt.time = currentTime;
    pt.value = (currentTime == impulseTime) ? amplitude : 0.0f;
    currentTime += samplingTime;
    return pt;
}

Point<float> DeltaGenerator::getNthSample(int n) const {
    float t = n * samplingTime;
    Point<float> pt;
    pt.time = t;
    pt.value = (t == impulseTime) ? amplitude : 0.0f;
    return pt;
}

void DeltaGenerator::reset() {
    currentTime = 0.0f;
}
