#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include "../common/signal.hpp"

#include "signal_generators/step_generator.hpp"
#include "signal_generators/ramp_generator.hpp"
#include "signal_generators/delta_generator.hpp"
#include "signal_generators/exp_generator.hpp"
#include "signal_generators/sawtooth_generator.hpp"
#include "signal_generators/triangle_generator.hpp"
#include "utils/helper.hpp"

struct TestResult
{
    const char *name;
    int passed;
    int total;
    int failed;
};

template <typename Generator>
using GenFunc = Point<float> (Generator::*)();
void testSignalCompare()
{
    std::cout << "\nRunning Signal::compare() test...\n";

    Signal<float> sig1, sig2, diff;
    sig1.setSamplingTime(1.0f);
    sig2.setSamplingTime(1.0f);

    for (int i = 0; i < 5; ++i)
    {
        sig1.addPoint(static_cast<float>(i), 2.0f * i);
        sig2.addPoint(static_cast<float>(i), 1.0f * i);
    }

    sig1.compare(sig2, diff);

    for (int i = 0; i < diff.size(); ++i)
    {
        float expected = static_cast<float>(i);
        if (!float_equal(diff[i].value, expected))
        {
            std::cout << "  [FAIL] Index " << i << ": got " << diff[i].value << ", expected " << expected << "\n";
        }
        else
        {
            std::cout << "  [PASS] Index " << i << ": value = " << diff[i].value << "\n";
        }
    }
}

template <typename Generator>
TestResult check_generator(
    const char *name,
    Generator *gen,
    GenFunc<Generator> method,
    const float expected_times[],
    const float expected_values[],
    int num_samples)
{
    TestResult result = {name, 0, num_samples, 0};

    for (int i = 0; i < num_samples; i++)
    {
        Point<float> pt = (gen->*method)();
        bool pass_time = float_equal(pt.time, expected_times[i]);
        bool pass_value = float_equal(pt.value, expected_values[i]);
        if (!pass_time || !pass_value)
        {
            printf("FAIL [%s] sample %d\n", name, i);
            printf("    Expected time: %.4f, Actual: %.4f\n", expected_times[i], pt.time);
            printf("    Expected val : %.4f, Actual: %.4f\n", expected_values[i], pt.value);
            result.failed++;
        }
        else
        {
            result.passed++;
        }
    }

    if (result.failed == 0)
    {
        printf("PASS %s [%d/%d]\n\n", name, result.passed, result.total);
    }
    else
    {
        printf("FAIL %s [%d/%d]\n\n", name, result.passed, result.total);
    }

    return result;
}

int main()
{
    const int no_of_samples = 41;

    StepGenerator<float> stepGen(1.0f, 0.0f, 1.0f);
    RampGenerator<float> rampGen(2.0f, 1.0f);
    DeltaGenerator<float> deltaGen(5.0f, 0.0f, 1.0f);
    ExponentialGenerator<float> expGen(1.0f, 1.0f, 1.0f);
    SawtoothGenerator<float> sawGen(1.0f, 20.0f, 1.0f);
    TriangleGenerator<float> triGen(1.0f, 40.0f, 1.0f);

    float times[no_of_samples];
    float step_vals[no_of_samples];
    float ramp_vals[no_of_samples];
    float delta_vals[no_of_samples];
    float exp_vals[no_of_samples];
    float saw_vals[no_of_samples];
    float tri_vals[no_of_samples];

    for (int i = 0; i < no_of_samples; ++i)
    {
        times[i] = static_cast<float>(i);
        step_vals[i] = 1.0f;
        ramp_vals[i] = 2.0f * i;
        delta_vals[i] = (i == 0) ? 5.0f : 0.0f;
    }

    float exp_values[no_of_samples] = {
        1.0000f, 0.3679f, 0.1353f, 0.0498f, 0.0183f, 0.0067f, 0.0025f, 0.0009f,
        0.0003f, 0.0001f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f,
        0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f,
        0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f,
        0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f,
        0.0000f};
    memcpy(exp_vals, exp_values, sizeof(exp_values));

    float saw_values[no_of_samples] = {
        -1.0000f, -0.9000f, -0.8000f, -0.7000f, -0.6000f, -0.5000f, -0.4000f,
        -0.3000f, -0.2000f, -0.1000f, 0.0000f, 0.1000f, 0.2000f, 0.3000f, 0.4000f,
        0.5000f, 0.6000f, 0.7000f, 0.8000f, 0.9000f, -1.0000f, -0.9000f, -0.8000f,
        -0.7000f, -0.6000f, -0.5000f, -0.4000f, -0.3000f, -0.2000f, -0.1000f,
        0.0000f, 0.1000f, 0.2000f, 0.3000f, 0.4000f, 0.5000f, 0.6000f, 0.7000f,
        0.8000f, 0.9000f, -1.0000f};
    memcpy(saw_vals, saw_values, sizeof(saw_values));

    float tri_values[no_of_samples] = {
        -1.0000f, -0.9000f, -0.8000f, -0.7000f, -0.6000f, -0.5000f, -0.4000f,
        -0.3000f, -0.2000f, -0.1000f, 0.0000f, 0.1000f, 0.2000f, 0.3000f, 0.4000f,
        0.5000f, 0.6000f, 0.7000f, 0.8000f, 0.9000f, 1.0000f, 0.9000f, 0.8000f,
        0.7000f, 0.6000f, 0.5000f, 0.4000f, 0.3000f, 0.2000f, 0.1000f, -0.0000f,
        -0.1000f, -0.2000f, -0.3000f, -0.4000f, -0.5000f, -0.6000f, -0.7000f,
        -0.8000f, -0.9000f, -1.0000f};
    memcpy(tri_vals, tri_values, sizeof(tri_values));

    TestResult results[6];
    results[0] = check_generator("Step", &stepGen, &StepGenerator<float>::generateNext, times, step_vals, no_of_samples);
    results[1] = check_generator("Ramp", &rampGen, &RampGenerator<float>::generateNext, times, ramp_vals, no_of_samples);
    results[2] = check_generator("Delta", &deltaGen, &DeltaGenerator<float>::generateNext, times, delta_vals, no_of_samples);
    results[3] = check_generator("Exponential", &expGen, &ExponentialGenerator<float>::generateNext, times, exp_vals, no_of_samples);
    results[4] = check_generator("Sawtooth", &sawGen, &SawtoothGenerator<float>::generateNext, times, saw_vals, no_of_samples);
    results[5] = check_generator("Triangle", &triGen, &TriangleGenerator<float>::generateNext, times, tri_vals, no_of_samples);

    int total_passed = 0, total_failed = 0;

    printf("----------- TEST SUMMARY -----------\n");
    for (int i = 0; i < 6; ++i)
    {
        if (results[i].failed == 0)
        {
            printf("PASS  %-12s %3d/%3d\n", results[i].name, results[i].passed, results[i].total);
            total_passed++;
        }
        else
        {
            printf("FAIL  %-12s %3d/%3d\n", results[i].name, results[i].passed, results[i].total);
            total_failed++;
        }
    }
    printf("------------------------------------\n");
    printf("TOTAL: %d passed, %d failed\n", total_passed, total_failed);

    testSignalCompare(); // Optional test for comparator logic
    return (total_failed > 0) ? 1 : 0;
}
