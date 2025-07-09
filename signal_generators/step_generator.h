#ifndef SINGEN_STEP_H
#define SINGEN_STEP_H

#include "../common/constants.h"

typedef struct {
    float amplitude;
    float stepTime;
    float samplingTime;
    float currentTime;
} StepGenerator;

void stepGeneratorInit(StepGenerator *gen, float amplitude, float stepTime, float samplingTime);
PointType generateStep(StepGenerator *gen);

#endif
