/**
 * @file cubes.c
 * @brief Backgammon cubes module implementation: draws two random numbers (1-6).
 */

#include "cubes.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Returns a string of dots for a die face.
 * @param n The die value (1-6).
 * @return A string of dots representing the face.
 */
static const char *dots(int n)
{
    static const char *const faces[] = {"   ", " o ", "o o", "o o", "o o", "o o", "o o"};
    return faces[n];
}

/**
 * @brief Prints two random dice values (backgammon cubes).
 * @return 0 on success.
 */
int print_cubes(void)
{
    srand((unsigned int)time(NULL));
    int die1 = (rand() % 6) + 1;
    int die2 = (rand() % 6) + 1;

    /* Draw two impressive dice with dots */
    printf("  +-----+     +-----+\n");
    printf("  |  %d  |     |  %d  |\n", die1, die2);
    printf("  +-----+     +-----+\n");
    printf("  |%s|     |%s|\n", dots(die1), dots(die2));
    printf("  +-----+     +-----+\n");

    return 0;
}
