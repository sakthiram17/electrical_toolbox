#include "../common/constants.h"
#include <math.h>
#include "singen.h"

void sineGeneratorInit(SineGenerator *generator, float frequency, float amplitude, float phase, float samplingTime)
{
    generator->frequency = frequency;
    generator->amplitude = amplitude;
    generator->phase = phase;
    generator->samplingTime = samplingTime;
    generator->currentTime = 0.0f;
}
PointType generateSineWave(SineGenerator *generator)
{
    PointType point;
    point.time = generator->currentTime;
    point.value = generator->amplitude  * sinf(2.0 * PI *generator->frequency * generator->currentTime + generator->phase);
    generator->currentTime += generator->samplingTime;
    return point;
}
