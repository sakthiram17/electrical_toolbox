#include "../common/signal.hpp"
#include <iostream>
template <typename timeType>
class Integrator
{
    double running_sum;
    timeType prev_time;
    bool is_first_sample = true;
    double lowerBound;
    double upperBound;

public:
    Integrator()
    {
        running_sum = 0;
        prev_time = 0.0;
        lowerBound = -1e6;
        upperBound = 1e6;
    }
    Integrator(double lowerBound, double UpperBound)
        : lowerBound(lowerBound), upperBound(UpperBound)
    {
        running_sum = 0;
        prev_time = 0.0;
        is_first_sample = true;
    }
    void reset()
    {
        running_sum = 0;
        prev_time = 0;
        is_first_sample = true;
    }
    double integrate(Point<timeType> point)
    {
        if (is_first_sample)
        {
            is_first_sample = false;
            prev_time = point.time;
            return 0;
        }
        double delta_time = static_cast<double>(point.time - prev_time);
        if (delta_time > 0)
        {
            running_sum += static_cast<double>(point.value) * delta_time;
            prev_time = point.time;
        }
        if (running_sum >= upperBound)
        {
            return upperBound;
        }
        if (running_sum <= lowerBound)
        {
            return lowerBound;
        }
        return running_sum;
    }
    double getValue() const
    {
        return running_sum;
    }
};