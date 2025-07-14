#include "../common/constants.h"
#include <stdio.h>
#include <stdlib.h>

void logger(const char *filename, PointType *points, int count) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("File opening failed");
        return;
    }
    fprintf(fp, "x,y\n");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%lf,%lf\n", points[i].time, points[i].value);
    }
    fclose(fp);
}