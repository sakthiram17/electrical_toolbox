#include "rectgen.h"
#include <math.h>
#include "../common/constants.h"

void rectGeneratorInit(RectWaveGenerator *generator, float frequency, float phase, float samplingTime, float dutyCycle , float highValue, float lowValue){
    generator->frequency = frequency;
    generator->highValue = highValue;
    generator->phase = phase;
    generator->samplingTime = samplingTime;
    generator->currentTime = 0.0f;
    generator->dutyCycle = dutyCycle;
    generator->lowValue = lowValue;
}


PointType generateRectWave(RectWaveGenerator *generator)
{
    PointType point;
    point.time = generator->currentTime;
    float period = 1.0f / generator->frequency;
    float onTime = generator->dutyCycle * period;

    // Compute time within the current period
    float t_shifted = generator->currentTime + generator->phase / (2.0f * PI * generator->frequency);
    float t_in_period = fmodf(t_shifted, period);

    if (t_in_period < onTime) {
        point.value = generator->highValue;
    } else {
        point.value = -generator->lowValue;
    }

    generator->currentTime += generator->samplingTime;
    return point;
    return point;
}