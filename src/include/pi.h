/**
 * @file pi.h
 * @brief Pi module: prints the constant pi.
 */

#ifndef CORE_DUMP_PI_H
#define CORE_DUMP_PI_H

/**
 * @brief Print pi to 15 decimal places (3.141592653589793) to stdout.
 *
 * The value is computed as acos(-1.0), so the program links the math library (-lm).
 * @return 0 on success; nonzero if printing fails.
 */
int print_pi(void);

#endif
