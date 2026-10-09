/**
 * @file pi.c
 * @brief Pi module implementation: computes pi with acos() from the C math library.
 */

#include "pi.h"

#include <math.h>
#include <stdio.h>

int print_pi(void)
{
    return printf("%.15f\n", acos(-1.0)) < 0;
}
