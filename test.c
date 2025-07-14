#include <stdio.h>
#include <math.h>
#include <string.h>

#include "signal_generators/step_generator.h"
#include "signal_generators/ramp_generator.h"
#include "signal_generators/delta_generator.h"
#include "signal_generators/exp_generator.h"
#include "signal_generators/sawtooth_generator.h"
#include "signal_generators/triangle_generator.h"
#include "utils/helper.h"
#include "basic_signal_math/comparator.test.h"


typedef struct {
    const char *name;
    int passed;
    int total;
    int failed;
} TestResult;

TestResult check_generator(
    const char *name,
    PointType (*generate)(void *gen),
    void *gen,
    float expected_times[],
    float expected_values[],
    int num_samples)
{
    TestResult result = { name, 0, num_samples, 0 };

    for (int i = 0; i < num_samples; i++) {
        PointType pt = generate(gen);
        int pass_time = float_equal(pt.time, expected_times[i]);
        int pass_value = float_equal(pt.value, expected_values[i]);

        if (!pass_time || !pass_value) {
            printf("FAIL [%s] sample %d\n", name, i);
            printf("    Expected time: %.4f, Actual: %.4f\n", expected_times[i], pt.time);
            printf("    Expected val : %.4f, Actual: %.4f\n", expected_values[i], pt.value);
            result.failed++;
        } else {
            result.passed++;
        }
    }

    if (result.failed == 0) {
        printf("PASS %s [%d/%d]\n\n", name, result.passed, result.total);
    } else {
        printf("FAIL %s [%d/%d]\n\n", name, result.passed, result.total);
    }
    return result;
}

PointType wrapper_step(void *g) {
    return generateStep((StepGenerator *)g);
}
PointType wrapper_ramp(void *g) {
    return generateRamp((RampGenerator *)g);
}
PointType wrapper_delta(void *g) {
    return generateDelta((DeltaGenerator *)g);
}
PointType wrapper_exp(void *g) {
    return generateExponential((ExponentialGenerator *)g);
}
PointType wrapper_saw(void *g) {
    return generateSawtooth((SawtoothGenerator *)g);
}
PointType wrapper_tri(void *g) {
    return generateTriangle((TriangleGenerator *)g);
}

int main()
{
    StepGenerator stepGen;
    RampGenerator rampGen;
    DeltaGenerator deltaGen;
    ExponentialGenerator expGen;
    SawtoothGenerator sawGen;
    TriangleGenerator triGen;
    int no_of_samples = 41;

    stepGeneratorInit(&stepGen, 1.0f, 0.0f, 1.0f);
    rampGeneratorInit(&rampGen, 2.0f, 1.0f);
    deltaGeneratorInit(&deltaGen, 5.0f, 0.0f, 1.0f);
    exponentialGeneratorInit(&expGen, 1.0f, 1.0f, 1.0f);
    sawtoothGeneratorInit(&sawGen, 1.0f, 20.0f, 1.0f);
    triangleGeneratorInit(&triGen, 1.0f, 40.0f, 1.0f);

    float times[41];
    for (int i = 0; i < no_of_samples; i++) {
        times[i] = (float)i;
    }

    float step_vals[41];
    float ramp_vals[41];
    float delta_vals[41];
    float exp_vals[41];
    float saw_vals[41];
    float tri_vals[41];

    for (int i = 0; i < no_of_samples; i++) {
        step_vals[i] = 1.0f;
        ramp_vals[i] = 2.0f * i;
        delta_vals[i] = (i == 0) ? 5.0f : 0.0f;
    }

    float exp_values[41] = {
        1.0000f, 0.3679f, 0.1353f, 0.0498f, 0.0183f, 0.0067f, 0.0025f, 0.0009f,
        0.0003f, 0.0001f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f,
        0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f,
        0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f,
        0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f,
        0.0000f };
    memcpy(exp_vals, exp_values, sizeof(exp_values));

    float saw_values[41] = {
        -1.0000f, -0.9000f, -0.8000f, -0.7000f, -0.6000f, -0.5000f, -0.4000f,
        -0.3000f, -0.2000f, -0.1000f, 0.0000f, 0.1000f, 0.2000f, 0.3000f, 0.4000f,
        0.5000f, 0.6000f, 0.7000f, 0.8000f, 0.9000f, -1.0000f, -0.9000f, -0.8000f,
        -0.7000f, -0.6000f, -0.5000f, -0.4000f, -0.3000f, -0.2000f, -0.1000f,
        0.0000f, 0.1000f, 0.2000f, 0.3000f, 0.4000f, 0.5000f, 0.6000f, 0.7000f,
        0.8000f, 0.9000f, -1.0000f
    };
    memcpy(saw_vals, saw_values, sizeof(saw_values));

    float tri_values[41] = {
        -1.0000f, -0.9000f, -0.8000f, -0.7000f, -0.6000f, -0.5000f, -0.4000f,
        -0.3000f, -0.2000f, -0.1000f, 0.0000f, 0.1000f, 0.2000f, 0.3000f, 0.4000f,
        0.5000f, 0.6000f, 0.7000f, 0.8000f, 0.9000f, 1.0000f, 0.9000f, 0.8000f,
        0.7000f, 0.6000f, 0.5000f, 0.4000f, 0.3000f, 0.2000f, 0.1000f, -0.0000f,
        -0.1000f, -0.2000f, -0.3000f, -0.4000f, -0.5000f, -0.6000f, -0.7000f,
        -0.8000f, -0.9000f, -1.0000f
    };
    memcpy(tri_vals, tri_values, sizeof(tri_values));

    TestResult results[6];
    int total_passed = 0;
    int total_failed = 0;

    results[0] = check_generator("Step", wrapper_step, &stepGen, times, step_vals, no_of_samples);
    results[1] = check_generator("Ramp", wrapper_ramp, &rampGen, times, ramp_vals, no_of_samples);
    results[2] = check_generator("Delta", wrapper_delta, &deltaGen, times, delta_vals, no_of_samples);
    results[3] = check_generator("Exponential", wrapper_exp, &expGen, times, exp_vals, no_of_samples);
    results[4] = check_generator("Sawtooth", wrapper_saw, &sawGen, times, saw_vals, no_of_samples);
    results[5] = check_generator("Triangle", wrapper_tri, &triGen, times, tri_vals, no_of_samples);

    printf("----------- TEST SUMMARY -----------\n");
    for (int i = 0; i < 6; i++) {
        if (results[i].failed == 0) {
            printf("PASS  %-12s %3d/%3d\n", results[i].name, results[i].passed, results[i].total);
            total_passed++;
        } else {
            printf("FAIL  %-12s %3d/%3d\n", results[i].name, results[i].passed, results[i].total);
            total_failed++;
        }
    }
    printf("------------------------------------\n");
    printf("TOTAL: %d passed, %d failed\n", total_passed, total_failed);
    comparator_test();

    return (total_failed > 0) ? 1 : 0;
}
