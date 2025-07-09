#ifndef SINGEN_TRIANGLE_H
#define SINGEN_TRIANGLE_H

#include "../common/constants.h"

typedef struct {
    float amplitude;
    float period;
    float samplingTime;
    float currentTime;
} TriangleGenerator;

void triangleGeneratorInit(TriangleGenerator *gen, float amplitude, float period, float samplingTime);
PointType generateTriangle(TriangleGenerator *gen);

#endif
