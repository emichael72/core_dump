/**
 * @file crc32.h
 * @brief CRC32 module: prints the CRC32 of the user's name as hex.
 */

#ifndef CORE_DUMP_CRC32_H
#define CORE_DUMP_CRC32_H

/**
 * @brief Print the CRC32 of "Eitan Michaelson" as hex (e.g. 0xaabbccdd) to stdout.
 * @return 0 on success; nonzero if printing fails.
 */
int print_crc32(void);

#endif
