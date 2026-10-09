/**
 * @file crc32.c
 * @brief CRC32 module implementation: returns the CRC32 of the user's name as hex.
 */

#include "crc32.h"

#include <stdio.h>
#include <stdint.h>

/**
 * @brief Compute the CRC32 of "Eitan Michaelson" and print as hex (e.g. 0xaabbccdd).
 * @return 0 on success; nonzero if printing fails.
 */
int print_crc32(void)
{
    static const char *name = "Eitan Michaelson";
    uint32_t crc = 0xFFFFFFFF;

    while (*name) {
        crc ^= (uint8_t)*name++;
        for (int j = 0; j < 8; j++) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
        }
    }

    return printf("0x%08x\n", crc ^ 0xFFFFFFFF) < 0;
}
