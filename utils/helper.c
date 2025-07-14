#include <math.h>
#include "../utils/helper.h"
#include "../common/constants.h"
#include <stdio.h>

int float_equal(float a, float b)
{
    return fabsf(a - b) < EPSILON;
}

void print_signal(const char *name, Signal s)
{
    printf("Signal %s (length = %d):\n", name, s.length);
    for (int i = 0; i < s.length; i++)
    {
        printf("[%d] time = %.4f, value = %.4f\n", i, s.points[i].time, s.points[i].value);
    }
    printf("\n");
}
float get_value_at_time(Signal S, int n, float time, float emptyValue)
{
    for (int i = 0; i < n; i++)
    {
        if (S.points[i].time == time)
        {

            return S.points[i].value;
        }
    }
    return emptyValue;
}