#include "../common/signal.hpp"
#include <iostream>
template <typename timeType>
class Differentiator
{
    double slope;
    timeType prev_time;
    bool is_first_sample = true;
    double saturation_limit;
    double prev_value;

public:
    Differentiator() : slope(0), prev_time(0.0), saturation_limit(1e6) {}
    Differentiator(double saturation_limit)
        : slope(0), prev_time(0.0), saturation_limit(saturation_limit) {}
    void reset()
    {
        is_first_sample = true;
        slope = 0;
        prev_time = 0.0;
    }
    double differentiate(Point<timeType> point)
    {
        if (is_first_sample)
        {
            is_first_sample = false;
            prev_time = point.time;
            prev_value = point.value;
            return 0;
        }
        double delta_time = static_cast<timeType>(point.time - prev_time);
        slope = (point.value - prev_value) / delta_time;
        prev_value = point.value;
        prev_time = point.time;

        if (abs(slope) >= saturation_limit)
            return saturation_limit * (slope < 0 ? -1 : 1);
        else
        {
            return slope;
        }
    }
    double getValue() const
    {
        return slope;
    }
};