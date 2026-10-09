/**
 * @file sine.h
 * @brief Sine module: plots an animated sine wave in the terminal over time.
 */

#ifndef CORE_DUMP_SINE_H
#define CORE_DUMP_SINE_H

/**
 * @brief Plot a scrolling sine wave to stdout for the given number of seconds.
 *
 * The trace moves from left to right as time advances, redrawing about every 50 ms,
 * and returns once `seconds` have elapsed. Requires the math library (-lm).
 * @param seconds How long (in seconds) to keep plotting; must be positive.
 * @return 0 on success; nonzero if writing to stdout fails.
 */
int print_sine(double seconds);

#endif
