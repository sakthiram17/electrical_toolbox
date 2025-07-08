#include <stdio.h>
#include "signal_generators/singen.h"

int main()
{
    SineGenerator gen;
    sineGeneratorInit(&gen, 50.0f, 1.0f, 0.0f, 1.0f / 1000.0f);

    for (int i = 0; i < 100; i++)
    {
        PointType point = generateSineWave(&gen);
        printf("%.6f,%.6f\n", point.time, point.value);
    }

    return 0;
}