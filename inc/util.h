/* COPYRIHGT (C) HARRY CLARK 2024 */

/* MOTOROLA 68000 STANDALONE EMULATION LIBRARY */

/* THIS FILE PERTAINS TOWARDS THE MAIN ENCOMPASSING UTIL THAT WILL */
/* BE USED IN THE MAIN EXECUTION OF THE PROGRAM */

#ifndef LIB68K_UTIL
#define LIB68K_UTIL

/* NESTED INCLUDES */

#include "common.h"

/* SYSTEM INCLUDES */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#if defined(USE_UTIL)
    #define USE_UTIL
        #else
    #define USE_UTIL

    #define         LIB_ID                  "LIB68K"

    #define         MAX_PATH_BUFFER         1024
    #define         MAX_DIR_BUFFER          1024
    #define         MAX_LINE_BUFFER         200
    #define         MAX_BODY_BUFFER         300
    #define         MAX_OP_BUFFER           30
    #define         MAX_PROC                4
    #define         MAX_EA                  5
    #define         MAX_OPCODE_INPUT        1000      
    #define         MAX_OPCODE_TABLE        3000

#endif

#endif