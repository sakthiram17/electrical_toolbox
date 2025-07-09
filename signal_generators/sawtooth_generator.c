#include "../common/constants.h"
#include "sawtooth_generator.h"
#include <math.h>

void sawtoothGeneratorInit(SawtoothGenerator *gen, float amplitude, float period, float samplingTime) {
    gen->amplitude = amplitude;
    gen->period = period;
    gen->samplingTime = samplingTime;
    gen->currentTime = 0.0f;
}

PointType generateSawtooth(SawtoothGenerator *gen) {
    PointType pt;
    pt.time = gen->currentTime;
    float t_mod = fmodf(gen->currentTime, gen->period);
    pt.value = (2.0f * gen->amplitude / gen->period) * t_mod - gen->amplitude;
    gen->currentTime += gen->samplingTime;
    return pt;
}
