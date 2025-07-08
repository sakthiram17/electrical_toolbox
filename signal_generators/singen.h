 #ifndef SINEGEN_H
#define SINEGEN_H

#include "../common/constants.h"

/**
 * Struct representing a sine wave generator.
 */
typedef struct SineGenerator
{
    float frequency;      // Frequency of the sine wave in Hz
    float amplitude;      // Amplitude of the sine wave
    float phase;          // Initial phase in radians
    float samplingTime;   // Sampling time (1/fs) in seconds
    float currentTime;    // Current time in seconds
} SineGenerator;

/**
 * Initialize a SineGenerator.
 * 
 * @param generator Pointer to the generator struct.
 * @param frequency Frequency in Hz.
 * @param amplitude Amplitude.
 * @param phase Initial phase in radians.
 * @param samplingTime Sampling period in seconds.
 */
void sineGeneratorInit(SineGenerator *generator, float frequency, float amplitude, float phase, float samplingTime);

/**
 * Generate the next sample of the sine wave.
 *
 * @param generator Pointer to the generator struct.
 * @return PointType containing time and value.
 */
PointType generateSineWave(SineGenerator *generator);

#endif // SINEGEN_H
