#ifndef LOGGER_H
#define LOGGER_H

#include <stddef.h>

typedef struct {
    double x;
    double y;
} PointType;

void logger(const char *filename, PointType *points, size_t count);

#endif // LOGGER_H
