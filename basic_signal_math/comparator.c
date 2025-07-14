#include "../common/constants.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include "comparator.h"

Signal *compare_signals(Signal x1, Signal x2, int n1, int n2, float emptyValue)
{
    const int start = fminf(x1.points[0].time, x2.points[0].time);
    const int end = fmaxf(x1.points[n1 - 1].time, x2.points[n2 - 1].time);
    const int Length = (end - start) + 1;
    const float time_interval = (int)fminf(x1.samplingTime, x2.samplingTime);
    Signal *x3 = malloc(sizeof(Signal) * Length);
    PointType *x3_points = malloc(sizeof(PointType) * Length);
    float current_time = start;
    for (int t = 0; t < Length; t++)
    {
        float v1 = get_value_at_time(x1, n1, t, emptyValue);
        float v2 = get_value_at_time(x2, n2, t, emptyValue);
        x3_points[t].time = current_time;
        x3_points[t].value = v1 - v2;
        current_time += time_interval;
    }
    x3->points = x3_points;
    x3->length = Length;
    return x3;
}