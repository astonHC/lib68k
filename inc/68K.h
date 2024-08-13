/* COPYRIHGT (C) HARRY CLARK 2024 */

/* MOTOROLA 68000 STANDALONE EMULATION LIBRARY */

/* THIS FILE PERTAINS TOWARDSS THE MAIN FUNCTIONALITY SURROUNDING THE UTILITY */
/* OF THE CPU AND IT'S SUBSEQUENT DIRECTIVES AND DEFINES */

/* ANY AND ALL OF THE CORRESPONDING DEFINES AND DECLARATIONS CAN BE */
/* ATTRIBUTED TO THE INFROMATION FOUND HERE: https://www.nxp.com/docs/en/reference-manual/M68000PRM.pdf  */ 

#ifndef M68K_BASE
#define M68K_BASE

/* NESTED INCLUDES */

#include "common.h"

/* SYSTEM INCLUDES */

#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>

#if defined(USE_68K)
    #define USE_68K
        #else
        #define USE_68K

    #if defined(USE_CONFIG)
    #define USE_CONFIG
        #else
    #define USE_CONFIG
    #include "68KCONF.h"
#endif

/*===============================================================================*/
/*							68000 MAIN CPU FUNCTIONALIY							 */
/*===============================================================================*/

#define         M68K_ADDRESS_WIDTH_8            0xFF
#define         M68K_ADDRESS_WIDTH_16           0xFFFF
#define         M68K_ADDRESS_WIDTH_32           0xFFFFFFFF
#define         M68K_SYMBOL_WIDTH               ' '
#define         M68K_ADDRESS_IA                 (0x8000000 << 0xDFFFFFF)

/*===============================================================================*/
/*-------------------------------------------------------------------------------*/
/*                          68000 MEMORY UTILITY MACROS                          */
/*                      FOR READING THE BYTE ORDER OF MEMORY                     */
/*-------------------------------------------------------------------------------*/
/*              THE FOLLOWING MACROS ARE DESIGNED FOR READING MEMORY             */
/*                      FROM A PREDEFINED MEMORY MAPPER                          */

/*                      BY BITSHIFTING THE CORRESPONDING BITS                    */
/*                      TO THE DESIGNATED DATA TYPE                              */
/*-------------------------------------------------------------------------------*/
/*===============================================================================*/

#define         M68K_READ_BYTE(VALUE, ADDRESS)              (VALUE)[(ADDRESS) ^ 1]
#define         M68K_READ_WORD(VALUE, ADDRESS)              (((VALUE)[ADDRESS]<<8) | (VALUE)[(ADDRESS)+1])

#define         M68K_READ_WORD_LONG(VALUE, ADDRESS)         (((VALUE)[(ADDRESS)+1]<<24) |       \
                                    		                ((VALUE)[(ADDRESS)]<<16) |  		\
                                    		                ((VALUE)[(ADDRESS )+3]<<8) |   		\
                                    		                (VALUE)[(ADDRESS)+2])


#define         M68K_CPU_000                0
#define         M68K_CPU_010                1
#define         M68K_CPU_020                2
#define         M68K_CPU_030                3
#define         M68K_CPU_040                4

#endif
#endif
