/**
 * @file joke.c
 * @brief Joke module implementation: prints a random joke about a given name.
 */

#include "joke.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/** @brief Five static jokes about Eitan, one selected at random. */
static const char *jokes[] = {
    "Why did Eitan cross the road? To prove he wasn't just a segmentation fault.",
    "Eitan walked into a bar. The bartender said, 'We don't serve your type here.' Eitan said, 'That's fine, I'm "
    "statically linked.'",
    "What do you call an Eitan who writes good code? A developer.",
    "Eitan's favorite exercise is a close call with malloc — he just keeps running out of breath.",
    "Why was Eitan bad at hide and seek? Because he always returned NULL."};

/** @brief Number of jokes in jokes[]. */
static const int num_jokes = sizeof(jokes) / sizeof(jokes[0]);

int print_joke(const char *name)
{
    srand((unsigned int)time(NULL));
    int index = rand() % num_jokes;
    const char *joke = jokes[index];

    /* Replace the placeholder name in the joke with the actual name */
    const char *placeholder = "Eitan";
    size_t placeholder_len = strlen(placeholder);
    size_t name_len = strlen(name);

    /* Allocate space for the new joke string */
    size_t joke_len = strlen(joke);
    char *result = malloc(joke_len - placeholder_len + name_len + 1);
    if (result == NULL)
        return -1;

    const char *pos = strchr(joke, 'E');
    if (pos == NULL) {
        strcpy(result, joke);
    } else {
        size_t prefix_len = pos - joke;
        memcpy(result, joke, prefix_len);
        memcpy(result + prefix_len, name, name_len);
        strcpy(result + prefix_len + name_len, pos + placeholder_len);
    }

    int ret = printf("%s\n", result) < 0;
    free(result);
    return ret;
}
