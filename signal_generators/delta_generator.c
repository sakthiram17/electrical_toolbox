#include "../common/constants.h"
#include "delta_generator.h"

void deltaGeneratorInit(DeltaGenerator *gen, float amplitude, float impulseTime, float samplingTime) {
    gen->amplitude = amplitude;
    gen->impulseTime = impulseTime;
    gen->samplingTime = samplingTime;
    gen->currentTime = 0.0f;
}

PointType generateDelta(DeltaGenerator *gen) {
    PointType pt;
    pt.time = gen->currentTime;
    pt.value = (gen->currentTime == gen->impulseTime) ? gen->amplitude : 0.0f;
    gen->currentTime += gen->samplingTime;
    return pt;
}
