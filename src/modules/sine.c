/**
 * @file sine.c
 * @brief Sine module implementation: plots an animated terminal sine wave.
 */

#include "sine.h"

#include <math.h>
#include <stdio.h>
#include <time.h>

#ifndef M_PI
/** @brief Value of pi when not provided by math.h. */
#define M_PI 3.14159265358979323846
#endif

int print_sine(double seconds)
{
    const double amplitude = 1.0;
    const int width = 40; /* terminal columns the wave spans   */
    const double freq = 2.0; /* cycles per second                 */
    const long frame_nsecs = 50000000L; /* ~20 frames per second          */

    unsigned long frames = (unsigned long)(seconds * 1000000000.0 / frame_nsecs);
    if (frames < 1)
        frames = 1;

    for (unsigned long f = 0; f < frames; ++f) {
        double t = (double)f * frame_nsecs / 1000000000.0;
        int col = (int)((sin(2.0 * M_PI * freq * t) + amplitude) / (2.0 * amplitude) * width);
        struct timespec delay = {0, frame_nsecs};

        for (int i = 0; i < col; ++i)
            putchar(' ');
        putchar('#');
        if (fflush(stdout) == EOF)
            return 1;
        nanosleep(&delay, NULL);
    }
    putchar('\n');

    return fflush(stdout) == EOF ? 1 : 0;
}
