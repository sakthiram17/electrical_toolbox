#include <stdio.h>
#include "signal_generators/singen.h"
#include "signal_generators/rectgen.h"

int main()
{
    RectWaveGenerator gen;
    rectGeneratorInit(&gen, 1.0f, 0, 0.01f, 0.03, 10,-5);
    for (int i = 0; i < 100; i++)
    {
        PointType point = generateRectWave(&gen);
        printf("%.6f,%.6f\n", point.time, point.value);
    }

    return 0;
}