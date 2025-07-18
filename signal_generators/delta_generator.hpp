#ifndef DELTA_GENERATOR_H
#define DELTA_GENERATOR_H

#include "../common/constants.hpp"

class DeltaGenerator {
private:
    float amplitude;
    float impulseTime;
    float samplingTime;
    float currentTime;

public:
    DeltaGenerator(float amplitude, float impulseTime, float samplingTime);

    Point<float> generateNext();
    Point<float> getNthSample(int n) const;
    void reset();
};

#endif
