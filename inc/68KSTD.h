/* COPYRIHGT (C) HARRY CLARK 2024 */
/* MOTOROLA 68000 STANDALONE EMULATION LIBRARY */

/* THIS FILE PERTAINS TOWARDS THE EMULATOR'S OVERARCHING STDLIB FUNCTIONALITY */
/* AKIN TO THE LIKENESS OF GNU LIBC */

#ifndef M68K_STD_LIB
#define M68K_STD_LIB

/* NESTED INCLUDES */

#include "68K.h"
#include "common.h"

#if defined(USE_STD_LIB)
    #define USE_STD_LIB
#else
    #define USE_STD_LIB

    #define M68K_ERROR_EXIT(MESSAGE, ...)                           \
    do                                                              \ 
    {                                                               \
        fprintf(stderr, "Error: " MESSAGE "\n", ##__VA_ARGS__);     \
        exit(EXIT_FAILURE);                                         \
                                                                    \
    } while (0)


#endif
#endif
