#include "../common/constants.h"
#include "triangle_generator.h"
#include <math.h>

void triangleGeneratorInit(TriangleGenerator *gen, float amplitude, float period, float samplingTime) {
    gen->amplitude = amplitude;
    gen->period = period;
    gen->samplingTime = samplingTime;
    gen->currentTime = 0.0f;
}

PointType generateTriangle(TriangleGenerator *gen) {
    PointType pt;
    pt.time = gen->currentTime;
    float t_mod = fmodf(gen->currentTime, gen->period);
    float slope = (4.0f * gen->amplitude) / gen->period;

    if (t_mod < gen->period / 2.0f) {
        pt.value = slope * t_mod - gen->amplitude;
    } else {
        pt.value = -slope * (t_mod - gen->period / 2.0f) + gen->amplitude;
    }

    gen->currentTime += gen->samplingTime;
    return pt;
}
