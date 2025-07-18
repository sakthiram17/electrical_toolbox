#include <iostream>
#include "signal_generators/delta_generator.hpp"
#include "constants.hpp"

int main() {
    DeltaGenerator deltaGen(5.0f, 1.0f, 1.0f);  // amplitude, impulse time, sampling time
    int num_samples = 10;

    std::cout << "Testing Delta Generator:\n";
    for (int i = 0; i < num_samples; ++i) {
        Point<float> pt = deltaGen.generateNext();
        std::cout << "t=" << pt.time << ", value=" << pt.value << std::endl;
    }

    return 0;
}
