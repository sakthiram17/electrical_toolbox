#ifndef COMPARE_SIGNALS_H
#define COMPARE_SIGNALS_H

#include "../common/constants.h"

float get_value_at_time(Signal S, int n, float time, float emptyFill);
Signal* compare_signals(Signal x1, Signal x2, int n1, int n2, float emptyFill);

#endif