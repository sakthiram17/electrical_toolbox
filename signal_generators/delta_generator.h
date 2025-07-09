#ifndef SINGEN_DELTA_H
#define SINGEN_DELTA_H

#include "../common/constants.h"

typedef struct {
    float amplitude;
    float impulseTime;
    float samplingTime;
    float currentTime;
} DeltaGenerator;

void deltaGeneratorInit(DeltaGenerator *gen, float amplitude, float impulseTime, float samplingTime);
PointType generateDelta(DeltaGenerator *gen);

#endif
