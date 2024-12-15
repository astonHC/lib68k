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
#include <string.h>

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
    #define         MAX_MEMORY_SIZE         1024 * 1024

    /* ENUM STORE OF ALL OF THE POSSIBLE EFFECTIVE ADDRESING MODES */
    /* =========================================================== */
    /* KEY:                                                        */
    /* AI = ADDRESS REGISTER INDIRECT */
    /* PI = ADDRESS REGISTER INDIRECT WITH POST INCREMENT */
    /* PI7 = ADDRESS REGISTER 7 VER OF PI */
    /* PD = PRE-DECREMENT */
    /* PD7 = ADDRESS REGISRER 7 VER OF PD */
    /* DI = DISP. */
    /* IND = INDEX */
    /* =========================================================== */

    typedef enum M68K_EA_TYPES
    {
        EA_MODE_NONE,
        EA_MODE_AI,
        EA_MODE_PI,
        EA_MODE_PI7,
        EA_MODE_PD,
        EA_MODE_PD7,
        EA_MODE_DI,
        EA_MODE_IND,
        EA_MODE_WORD,
        EA_MODE_LONG,
        EA_MODE_PCDI,
        EA_MODE_PCIND,
        EA_MODE_I

    } M68K_EA_TYPES;

    typedef struct LIB_BASE
    {
        char INPUT_FILE[MAX_PATH_BUFFER];
        char OUTPUT_PATH[MAX_DIR_BUFFER];
        char* FILENMAE[MAX_PATH_BUFFER * 2];
        char* SECTION_ID[MAX_LINE_BUFFER + 1];
        char* FILE_PATH;

        int OPCODE_HANDLER_READ;

    } LIB_BASE;


/*====================================================*/
/*              FUNCTION DECLARATIVES                 */
/*====================================================*/

static FILE* INPUT;

void PROC_FILE(char* FILENAME);

#endif
#endif
