/**
 * @file main.c
 * @brief Command-line entry point of core_dump: parses the options and runs the modules in order.
 */

#include "crc32.h"
#include "cubes.h"
#include "joke.h"
#include "pi.h"
#include "sine.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief The short options, for both getopt_long passes in main(). A new option is added here once,
 *        next to its entry in main()'s options table.
 */
static const char short_options[] = "phcs:j:";

/**
 * @brief Print the command-line help.
 * @param stream Where to print it: stdout for --help, stderr after an invalid option.
 * @param program The program name shown in the usage line (argv[0]).
 */
static void usage(FILE *stream, const char *program)
{
    fprintf(stream,
            "Usage: %s [OPTIONS]\n"
            "  -p, --pi       Print pi to 15 decimal places\n"
            "  -c, --crc32    Print the CRC32 of the user's name as hex\n"
            "  -b, --cubes    Print two random dice values (backgammon cubes)\n"
            "  -s SECONDS, --sine=SECONDS  Plot an animated sine wave for SECONDS seconds\n"
            "  -j NAME, --joke=NAME  Print a random joke about NAME\n"
            "  -h, --help     Show this help\n"
            "\nOptions may be combined, e.g. -pp or --pi --help.\n",
            program);
}

/**
 * @brief Run the modules selected on the command line, in command-line order.
 *
 * The whole command line is validated before any module runs; with no arguments the help is shown.
 * @param argc Number of command-line arguments.
 * @param argv The command-line arguments; argv[0] is the program name.
 * @return EXIT_SUCCESS, or EXIT_FAILURE if an argument is invalid, a module fails or stdout cannot
 *         be flushed.
 */
int main(int argc, char **argv)
{
    static const struct option options[] = {
        {"pi",    no_argument,       NULL, 'p'},
        {"crc32", no_argument,       NULL, 'c'},
        {"cubes", no_argument,       NULL, 'b'},
        {"sine",  required_argument, NULL, 's'},
        {"joke",  required_argument, NULL, 'j'},
        {"help",  no_argument,       NULL, 'h'},
        {NULL,    0,                 NULL, 0  }
    };
    int option;

    if (argc == 1) {
        usage(stdout, argv[0]);
        return EXIT_SUCCESS;
    }

    /* Validate the entire command before dispatching any module. */
    opterr = 0;
    while ((option = getopt_long(argc, argv, short_options, options, NULL)) != -1) {
        if (option == '?') {
            fputs("core_dump: invalid option or unexpected option argument\n", stderr);
            usage(stderr, argv[0]);
            return EXIT_FAILURE;
        }
    }
    if (optind < argc) {
        fprintf(stderr, "core_dump: unexpected argument: %s\n", argv[optind]);
        return EXIT_FAILURE;
    }

    optind = 0; /* Reset GNU getopt for the dispatch pass on Linux. */
    while ((option = getopt_long(argc, argv, short_options, options, NULL)) != -1) {
        switch (option) {
        case 'p':
            if (print_pi() != 0)
                return EXIT_FAILURE;
            break;
        case 'c':
            if (print_crc32() != 0)
                return EXIT_FAILURE;
            break;
        case 'b':
            if (print_cubes() != 0)
                return EXIT_FAILURE;
            break;
        case 's': {
            char *end = NULL;
            double seconds = strtod(optarg, &end);
            if (optarg == end || *end != '\0' || seconds <= 0.0) {
                fputs("core_dump: invalid sine duration\n", stderr);
                return EXIT_FAILURE;
            }
            if (print_sine(seconds) != 0)
                return EXIT_FAILURE;
            break;
        }
        case 'j': {
            if (print_joke(optarg) != 0)
                return EXIT_FAILURE;
            break;
        }
        case 'h':
            usage(stdout, argv[0]);
            break;
        default:
            return EXIT_FAILURE;
        }
    }
    return fflush(stdout) == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}
