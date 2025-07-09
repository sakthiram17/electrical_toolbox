#ifndef SINGEN_RAMP_H
#define SINGEN_RAMP_H

#include "../common/constants.h"

typedef struct {
    float slope;
    float samplingTime;
    float currentTime;
} RampGenerator;

void rampGeneratorInit(RampGenerator *gen, float slope, float samplingTime);
PointType generateRamp(RampGenerator *gen);

#endif
