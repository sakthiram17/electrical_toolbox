#ifndef CONSTANTS_H
#define CONSTANTS_H

#define PI 3.14159265358979323846
#define EPSILON 1e-3

typedef struct {
    float time;
    float value;
} PointType;

typedef struct {
    PointType *points;
    int length;
    float samplingTime;
} Signal;

#endif