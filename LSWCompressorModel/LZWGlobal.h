//Taken from https://github.com/MichaelDipperstein/lzw
#pragma once
#include <limits.h>
#define MIN_CODE_LEN    9                   /* min # bits in a code word */
#define MAX_CODE_LEN    20                  /* max # bits in a code word */

#define FIRST_CODE      (1 << CHAR_BIT)     /* value of 1st string code */
#define MAX_CODES       (1 << MAX_CODE_LEN)

#if (MIN_CODE_LEN <= CHAR_BIT)
#error Code words must be larger than 1 character
#endif

#if ((MAX_CODES - 1) > INT_MAX)
#error There cannot be more codes than can fit in an integer
#endif

#define CURRENT_MAX_CODES(bits)     ((unsigned int)(1 << (bits)))
