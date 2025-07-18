#include "../common/signal.hpp"

template <typename TimeType>
class DeltaGenerator
{
private:
    float amplitude;
    TimeType impulseTime;
    TimeType samplingTime;
    TimeType currentTime;

public:
    DeltaGenerator(float amplitude, TimeType impulseTime, TimeType samplingTime)
        : amplitude(amplitude), impulseTime(impulseTime),
          samplingTime(samplingTime), currentTime(0) {}

    Point<TimeType> generateNext()
    {
        Point<TimeType> pt;
        pt.time = currentTime;
        pt.value = (fabs(currentTime - impulseTime) < EPSILON) ? amplitude : 0.0f;
        currentTime += samplingTime;
        return pt;
    }

    Point<TimeType> getNthSample(int n) const
    {
        TimeType t = static_cast<TimeType>(n) * samplingTime;
        Point<TimeType> pt;
        pt.time = t;
        pt.value = (fabs(t - impulseTime) < EPSILON) ? amplitude : 0.0f;
        return pt;
    }

    void reset()
    {
        currentTime = 0;
    }
};
