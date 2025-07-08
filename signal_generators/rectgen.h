 #ifndef RECTGEN_H
#define RECTGEN_H

#include "../common/constants.h"

/**
 * Struct representing a rectangular wave generator.
 */
typedef struct RectWaveGenerator
{
    float frequency;      // Frequency of the sine wave in Hz
    float phase;          // Initial phase in radians
    float samplingTime;   // Sampling time (1/fs) in seconds
    float currentTime;    // Current time in seconds
    float dutyCycle;
    float highValue;      // NEW
    float lowValue;       // NEW
} RectWaveGenerator;

void rectGeneratorInit(RectWaveGenerator *generator, float frequency, float phase, float samplingTime, float dutyCycle , float highValue, float lowValue);
PointType generateRectWave(RectWaveGenerator *generator);

#endif RECTGEN_H