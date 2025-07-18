#include <iostream>
#include <cmath>
#include "../signal_generators/delta_generator.hpp"
#include "../common/signal.hpp"

bool float_equal(float a, float b, float epsilon = 1e-4f) {
    return std::fabs(a - b) < epsilon;
}

void testDeltaGenerator() {
    std::cout << "Running DeltaGenerator test...\n";

    DeltaGenerator<float> gen(5.0f, 0.0f, 1.0f);
    int num_samples = 5;
    float expected_values[5] = {5.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    for (int i = 0; i < num_samples; ++i) {
        auto pt = gen.generateNext();
        if (!float_equal(pt.time, static_cast<float>(i)) ||
            !float_equal(pt.value, expected_values[i])) {
            std::cout << "  [FAIL] Sample " << i << ": time=" << pt.time
                      << ", value=" << pt.value << " (expected " << expected_values[i] << ")\n";
        } else {
            std::cout << "  [PASS] Sample " << i << ": time=" << pt.time
                      << ", value=" << pt.value << "\n";
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
        sig1.addPoint(static_cast<float>(i), 2.0f * i);  // 0,2,4,6,8
        sig2.addPoint(static_cast<float>(i), 1.0f * i);  // 0,1,2,3,4
    }

    sig1.compare(sig2, diff);

    for (int i = 0; i < diff.size(); ++i) {
        auto pt = diff[i];
        float expected = static_cast<float>(i);  // Difference should be i
        if (!float_equal(pt.value, expected)) {
            std::cout << "  [FAIL] Index " << i << ": got " << pt.value << ", expected " << expected << "\n";
        } else {
            std::cout << "  [PASS] Index " << i << ": value = " << pt.value << "\n";
        }
    }
}

int main() {
    testDeltaGenerator();
    testSignalCompare();
    return 0;
}
