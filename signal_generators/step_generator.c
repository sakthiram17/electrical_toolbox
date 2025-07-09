#include "../common/constants.h"
#include "step_generator.h"

void stepGeneratorInit(StepGenerator *gen, float amplitude, float stepTime, float samplingTime)
{
    gen->amplitude = amplitude;
    gen->stepTime = stepTime;
    gen->samplingTime = samplingTime;
    gen->currentTime = 0.0f;
}

PointType generateStep(StepGenerator *gen)
{
    PointType pt;
    pt.time = gen->currentTime;
    pt.value = (gen->currentTime >= gen->stepTime) ? gen->amplitude : 0.0f;
    gen->currentTime += gen->samplingTime;
    return pt;
}
