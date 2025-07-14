#include <stdio.h>
#include <assert.h>
#include "../common/constants.h"
#include "../basic_signal_math/comparator.h"
#include "../utils/helper.h"


int comparator_test()
{
    printf("\n=== comparator_test (uniform time steps) ===\n");

    // Signal 1: times 0,1,2, values 1, 2, 3
    PointType points1[] = {
        {0.0, 1.0},
        {1.0, 2.0},
        {2.0, 3.0}
    };

    // Signal 2: times 0,1,2, values 0.5, 1.5, 2.5
    PointType points2[] = {
        {1, 0.5},
        {2, 1.5},
        {3, 2.5}
    };

    Signal x1 = {points1, 3, 1.0f};
    Signal x2 = {points2, 3, 1.0f};

    float emptyFill = -0.0f;

    Signal *diff = compare_signals(x1, x2, x1.length, x2.length, emptyFill);

    float expected_times[] = {0.0, 1.0, 2.0 ,3 };
    float expected_values[] = {1, 1.5, 1.5,-2.5};
    int expected_len = 4;

    int all_pass = 1;

    printf("Input Signal x1:\n");
    print_signal("x1", x1);

    printf("Input Signal x2:\n");
    print_signal("x2", x2);

    printf("Expected Diff Signal:\n");
    for (int i = 0; i < expected_len; i++)
    {
        printf("  Index %d: time = %.4f, value = %.4f\n", i, expected_times[i], expected_values[i]);
    }
    printf("\n");

    if (diff->length != expected_len)
    {
        printf("FAIL: Diff signal length mismatch. Expected %d, got %d.\n\n", expected_len, diff->length);
        all_pass = 0;
    }

    int points_to_check = (diff->length < expected_len) ? diff->length : expected_len;

    for (int i = 0; i < points_to_check; i++)
    {
        int time_ok = float_equal(diff->points[i].time, expected_times[i]);
        int val_ok = float_equal(diff->points[i].value, expected_values[i]);

        if (!time_ok || !val_ok)
        {
            printf("FAIL at index %d\n", i);
            printf("  Expected time = %.4f, value = %.4f\n", expected_times[i], expected_values[i]);
            printf("  Actual time   = %.4f, value = %.4f\n", diff->points[i].time, diff->points[i].value);

            if (!time_ok)
                printf("  Time mismatch detected.\n");
            if (!val_ok)
                printf("  Value mismatch detected.\n");

            all_pass = 0;
        }
        else
        {
            printf("PASS at index %d: time = %.4f, value = %.4f\n",
                   i, diff->points[i].time, diff->points[i].value);
        }
    }

    if (!all_pass)
    {
        printf("\nComputed Diff Signal for debugging:\n");
        for (int i = 0; i < diff->length; i++)
        {
            printf("  Index %d: time = %.4f, value = %.4f\n",
                   i, diff->points[i].time, diff->points[i].value);
        }
        printf("\n");
    }

    if (all_pass)
    {
        printf("comparator_test PASSED all checks.\n\n");
    }
    else
    {
        printf("comparator_test FAILED.\n\n");
    }

    return all_pass;
}