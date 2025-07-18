#pragma once

#include <cmath>
#include <iostream>
#include "../common/constants.hpp"
#include "../common/signal.hpp"

template <typename TimeType>
bool float_equal(TimeType a, TimeType b)
{
    return std::fabs(a - b) < EPSILON;
}

template <typename TimeType>
void print_signal(const std::string& name, const Signal<TimeType>& s)
{
    std::cout << "Signal " << name << " (length = " << s.length << "):\n";;

    for (int i = 0; i < s.length; ++i)
    {
        std::cout << "[" << i << "] time = " 
                  << static_cast<float>(s.points[i].time)
                  << ", value = " << s.points[i].value << "\n";
    }
    std::cout << std::endl;
}

template <typename TimeType>
float get_value_at_time(const Signal<TimeType>& S, int n, TimeType time, float emptyValue)
{
    for (int i = 0; i < n; ++i)
    {
        if (float_equal(S.points[i].time, time))
        {
            return S.points[i].value;
        }
    }
    return emptyValue;
}
