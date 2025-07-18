#include "../common/constants.hpp"
#include "exp_generator.hpp
"

#include <math.h>

void exponentialGeneratorInit(ExponentialGenerator *gen, float amplitude, float tau, float samplingTime) {
    gen->amplitude = amplitude;
    gen->tau = tau;
    gen->samplingTime = samplingTime;
    gen->currentTime = 0.0f;
}

PointType generateExponential(ExponentialGenerator *gen) {
    PointType pt;
    pt.time = gen->currentTime;
    pt.value = gen->amplitude * expf(-gen->currentTime / gen->tau);
    gen->currentTime += gen->samplingTime;
    return pt;
}
