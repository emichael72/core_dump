/**
 * @file joke.h
 * @brief Joke module: prints a random joke about a given name.
 */

#ifndef CORE_DUMP_JOKE_H
#define CORE_DUMP_JOKE_H

/**
 * @brief Print a random joke about the given name to stdout.
 *
 * Selects one of five static jokes at random and prints it, inserting the name.
 * @param name The name to use in the joke (e.g., "Eitan").
 * @return 0 on success; nonzero if printing fails.
 */
int print_joke(const char *name);

#endif
