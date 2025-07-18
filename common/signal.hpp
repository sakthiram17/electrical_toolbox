#pragma once

#include <cmath>
#include "constants.hpp"

template <typename TimeType>
class Point
{
public:
    TimeType time;
    float value;

    Point() : time(0), value(0.0f) {}
    Point(TimeType t, float v) : time(t), value(v) {}
};

template <typename TimeType>
class Signal
{
public:
    Point<TimeType> points[MAX_SIGNAL_LENGTH];
    int length;
    TimeType samplingTime;

    Signal() : length(0), samplingTime(0) {}

    void addPoint(TimeType time, float value)
    {
        if (length < MAX_SIGNAL_LENGTH)
        {
            points[length++] = Point<TimeType>(time, value);
        }
    }

    const Point<TimeType> &operator[](int index) const
    {
        return points[index];
    }

    Point<TimeType> &operator[](int index)
    {
        return points[index];
    }

    void clear()
    {
        length = 0;
    }

    void setSamplingTime(TimeType ts)
    {
        samplingTime = ts;
    }

    TimeType getSamplingTime() const
    {
        return samplingTime;
    }

    int size() const
    {
        return length;
    }

    // Get value at a specific time (approx match within EPSILON)
    float getValueAtTime(TimeType time, float emptyValue = 0.0f) const
    {
        for (int i = 0; i < length; ++i)
        {
            if (std::abs(static_cast<float>(points[i].time - time)) < EPSILON)
            {
                return points[i].value;
            }
        }
        return emptyValue;
    }

    // Compare two signals (returns difference signal)
    void compare(const Signal<TimeType> &other, Signal<TimeType> &result, float emptyValue = 0.0f) const
    {
        TimeType start = min(points[0].time, other.points[0].time);
        TimeType end = max(points[length - 1].time, other.points[other.length - 1].time);
        TimeType dt = min(samplingTime, other.samplingTime);
        int newLen = static_cast<int>((end - start) / dt) + 1;

        result.clear();
        result.setSamplingTime(dt);

        if (newLen > MAX_SIGNAL_LENGTH)
            newLen = MAX_SIGNAL_LENGTH;

        TimeType t = start;
        for (int i = 0; i < newLen; ++i)
        {
            float v1 = getValueAtTime(t, emptyValue);
            float v2 = other.getValueAtTime(t, emptyValue);
            result.addPoint(t, v1 - v2);
            t += dt;
        }
    }
};
