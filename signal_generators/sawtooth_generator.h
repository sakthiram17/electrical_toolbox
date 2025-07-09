#ifndef SINGEN_SAWTOOTH_H
#define SINGEN_SAWTOOTH_H

#include "../common/constants.h"

typedef struct {
    float amplitude;
    float period;
    float samplingTime;
    float currentTime;
} SawtoothGenerator;

void sawtoothGeneratorInit(SawtoothGenerator *gen, float amplitude, float period, float samplingTime);
PointType generateSawtooth(SawtoothGenerator *gen);

#endif
