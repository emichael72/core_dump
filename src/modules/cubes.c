/**
 * @file cubes.c
 * @brief Backgammon cubes module implementation: draws two random numbers (1-6).
 */

#include "cubes.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int print_cubes(void)
{
    srand((unsigned int)time(NULL));
    int die1 = (rand() % 6) + 1;
    int die2 = (rand() % 6) + 1;

    /* Draw the dice in a terminal-friendly way */
    printf("┌───┬───┐\n");
    printf("│ %d │ %d │\n", die1, die2);
    printf("└───┴───┘\n");

    return 0;
}
