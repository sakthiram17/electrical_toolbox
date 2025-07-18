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

    const Point<TimeType> &operator[](size_t index) const
    {
        return points[index];
    }

    Point<TimeType> &operator[](size_t index)
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
    Signal compare(const Signal &other, float emptyValue = 0.0f) const
    {
        TimeType start = std::min(points[0].time, other.points[0].time);
        TimeType end = std::max(points[length - 1].time, other.points[other.length - 1].time);
        TimeType timeInterval = std::min(samplingTime, other.samplingTime);

        int newLength = static_cast<int>((end - start) / timeInterval) + 1;
        Signal result;
        result.length = newLength;
        result.samplingTime = timeInterval;

        TimeType currentTime = start;
        for (int i = 0; i < newLength; ++i)
        {
            float v1 = getValueAtTime(currentTime, emptyValue);
            float v2 = other.getValueAtTime(currentTime, emptyValue);

            result.points[i].time = currentTime;
            result.points[i].value = v1 - v2;

            currentTime += timeInterval;
        }

        return result;
    }
};
