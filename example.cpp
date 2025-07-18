#include <iostream>
#include <cmath>
#include "../signal_generators/delta_generator.hpp"
#include "../common/signal.hpp"
#include "../signal_generators/exp_generator.hpp"

bool float_equal(float a, float b, float epsilon = 1e-4f) {
    return std::fabs(a - b) < epsilon;
}

void testDeltaGenerator() {
    std::cout << "Running DeltaGenerator test...\n";

    DeltaGenerator<float> gen(5.0f, 0.0f, 1.0f);
    const int num_samples = 5;
    float expected_values[num_samples] = {5.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    for (int i = 0; i < num_samples; ++i) {
        Point<float> pt = gen.generateNext();
        if (!float_equal(pt.time, static_cast<float>(i)) || !float_equal(pt.value, expected_values[i])) {
            std::cout << "  [FAIL] Sample " << i << ": time=" << pt.time << ", value=" << pt.value
                      << " (expected " << expected_values[i] << ")\n";
        } else {
            std::cout << "  [PASS] Sample " << i << ": time=" << pt.time << ", value=" << pt.value << "\n";
        }
    }

    gen.reset();
}

void testExponentialGenerator() {
    std::cout << "\nRunning ExponentialGenerator test...\n";

    ExponentialGenerator<float> gen(1.0f, 2.0f, 1.0f);
    const int num_samples = 5;
    float expected_values[num_samples];

    for (int i = 0; i < num_samples; ++i) {
        expected_values[i] = 1.0f * std::exp(-i / 2.0f);
    }

    for (int i = 0; i < num_samples; ++i) {
        Point<float> pt = gen.generateNext();
        if (!float_equal(pt.value, expected_values[i])) {
            std::cout << "  [FAIL] Sample " << i << ": value=" << pt.value
                      << " (expected " << expected_values[i] << ")\n";
        } else {
            std::cout << "  [PASS] Sample " << i << ": value=" << pt.value << "\n";
        }
    }

    gen.reset();
}

void testSignalCompare() {
    std::cout << "\nRunning Signal::compare() test...\n";

    Signal<float> sig1, sig2, diff;
    sig1.setSamplingTime(1.0f);
    sig2.setSamplingTime(1.0f);

    for (int i = 0; i < 5; ++i) {
        sig1.addPoint(static_cast<float>(i), 2.0f * i);
        sig2.addPoint(static_cast<float>(i), 1.0f * i);
    }

    sig1.compare(sig2, diff);

    for (int i = 0; i < diff.size(); ++i) {
        float expected = static_cast<float>(i);
        if (!float_equal(diff[i].value, expected)) {
            std::cout << "  [FAIL] Index " << i << ": got " << diff[i].value << ", expected " << expected << "\n";
        } else {
            std::cout << "  [PASS] Index " << i << ": value = " << diff[i].value << "\n";
        }
    }
}

int main() {
    testDeltaGenerator();
    testExponentialGenerator();
    testSignalCompare();
    return 0;
}