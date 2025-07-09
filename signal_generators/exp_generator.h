#ifndef SINGEN_EXPONENTIAL_H
#define SINGEN_EXPONENTIAL_H

#include "../common/constants.h"

typedef struct {
    float amplitude;
    float tau;
    float samplingTime;
    float currentTime;
} ExponentialGenerator;

void exponentialGeneratorInit(ExponentialGenerator *gen, float amplitude, float tau, float samplingTime);
PointType generateExponential(ExponentialGenerator *gen);

#endif
