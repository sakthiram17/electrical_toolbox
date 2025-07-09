#include <stdio.h>
#include "signal_generators/step_generator.h"
#include "signal_generators/ramp_generator.h"
#include "signal_generators/delta_generator.h"
#include "signal_generators/exp_generator.h"
#include "signal_generators/sawtooth_generator.h"
#include "signal_generators/triangle_generator.h"

int main()
{
    StepGenerator stepGen;
    RampGenerator rampGen;
    DeltaGenerator deltaGen;
    ExponentialGenerator expGen;
    SawtoothGenerator sawGen;
    TriangleGenerator triGen;
    int no_of_samples = 41;

    stepGeneratorInit(&stepGen, 1.0f, 1.0f, 1.0f);
    rampGeneratorInit(&rampGen, 2.0f, 1.0f);
    deltaGeneratorInit(&deltaGen, 5.0f, 1.0f, 1.0f);
    exponentialGeneratorInit(&expGen, 1.0f, 1.0f, 1.0f);
    sawtoothGeneratorInit(&sawGen, 1.0f, 20.0f, 1.0f);
    triangleGeneratorInit(&triGen, 1.0f, 40.0f, 1.0f);

    printf("Testing Step:\n");
    for (int i = 0; i < no_of_samples; i++)
    {
        PointType pt = generateStep(&stepGen);
        printf("%.4f,%.4f\n", pt.time, pt.value);
    }

    printf("\nTesting Ramp:\n");
    for (int i = 0; i < no_of_samples; i++)
    {
        PointType pt = generateRamp(&rampGen);
        printf("%.4f,%.4f\n", pt.time, pt.value);
    }

    printf("\nTesting Delta:\n");
    for (int i = 0; i < no_of_samples; i++)
    {
        PointType pt = generateDelta(&deltaGen);
        printf("%.4f,%.4f\n", pt.time, pt.value);
    }

    printf("\nTesting Exponential:\n");
    for (int i = 0; i < no_of_samples; i++)
    {
        PointType pt = generateExponential(&expGen);
        printf("%.4f,%.4f\n", pt.time, pt.value);
    }

    printf("\nTesting Sawtooth:\n");
    for (int i = 0; i < no_of_samples; i++)
    {
        PointType pt = generateSawtooth(&sawGen);
        printf("%.4f,%.4f\n", pt.time, pt.value);
    }

    printf("\nTesting Triangle:\n");
    for (int i = 0; i < no_of_samples; i++)
    {
        PointType pt = generateTriangle(&triGen);
        printf("%.4f,%.4f\n", pt.time, pt.value);
    }

    return 0;
}
