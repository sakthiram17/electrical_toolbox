#include "../common/constants.h"
#include "ramp_generator.h"

void rampGeneratorInit(RampGenerator *gen, float slope, float samplingTime) {
    gen->slope = slope;
    gen->samplingTime = samplingTime;
    gen->currentTime = 0.0f;
}

PointType generateRamp(RampGenerator *gen) {
    PointType pt;
    pt.time = gen->currentTime;
    pt.value = gen->slope * gen->currentTime;
    gen->currentTime += gen->samplingTime;
    return pt;
}
