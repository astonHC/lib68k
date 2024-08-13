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

#define         M68K_IRQ_NONE               0
#define         M68K_IRQ_1                  1
#define         M68K_IRQ_2                  2
#define         M68K_IRQ_3                  3
#define         M68K_IRQ_4                  4
#define         M68K_IRQ_5                  5
#define         M68K_IRQ_6                  6
#define         M68K_IRQ_7                  7

typedef struct CPU_68K
{
    unsigned int PC;
    unsigned int* INSTRUCTION_CYCLES;
    unsigned int* CYCLE_RATE;
    unsigned char* MEMORY_BASE;
    unsigned int** CYCLE_EXCEPTION;

    unsigned(*MEMORY_DATA);
    unsigned(*MEMORY_ADDRESS);
    unsigned(*MEMORY_POINTER);

	unsigned(*LOW_ADDR);
	unsigned(*HIGH_ADDR);
	void(*USER_DATA);

	unsigned int* STOPPED;

    U16* STATUS_REGISTER;
	U32* INDEX_REGISTER;
    U32* REGISTER_BASE[16];
	U32* DATA_REGISTER[8];
	U32* ADDRESS_REGISTER[8];
    U32* PREVIOUS_PC;
    U32* STACK_POINTER;
	U32* INTERRUPT_SP;
	U32* MASTER_SP;
	U32* USER_STACK;
	U32* ADDRESS_STACK_POINTER;
    U32* INSTRUCTION_REGISTER;
	U32* SOURCE_FUNCTION_COUNTER;
	U32* DEST_FUNCTION_COUNTER;
	U32* VBR;
	U32* FPR[8];
	U32* FPIAR;
	U32* FPCR;
	U32* FPSR;
	U32* CACHE_CONTROL;
	U32* CACHE_ADDRESS;

    char* INSTRUCTION_MODE;
    char* TRACE_FLAG;

    unsigned int* PREVIOUS_DATA;
    unsigned int* PREVIOUS_ADDRESS;
    unsigned int* ADDRESS_RT_CHECK;
    unsigned char* ERROR_ADDRESS;
    unsigned char* ERROR_WRITE_MODE;
    unsigned char* ERROR_PC;
    UNK* ERROR_JUMP;

    S32(*INTERRUPT_CALLBACK)(unsigned INTERRUPT);
    S32(*RESET_INTERRUPT)(void);
    S32(*CPU_FUNC_CALLBACK)(unsigned FUNCTION);
	unsigned int* INT_LEVEL;

	unsigned* CPU_STOPPED;

	unsigned  S_FLAG;
	unsigned* X_FLAG;
	unsigned* N_FLAG;
	unsigned* V_FLAG;
	unsigned* Z_FLAG;
	unsigned* C_FLAG;
	unsigned  M_FLAG;

	unsigned* T0_FLAG;
	unsigned* T1_FLAG;

    int(*INT_ACK_CALLBACK)(int VALUE);
    void(*RESET_CALLBACK)(void);
    void(*PC_CHANGED_CALLBACK)(unsigned* NEW_PC);
    void(*SET_FC_CALLBACK)(unsigned* NEW_FC);
    void(*INSTR_HOOK)(unsigned* PC);

    CPU_68K_MEMORY MEMORY_MAP[256];

} CPU_68K;

typedef struct CPU_68K_MEMORY
{
    unsigned(*MEMORY_BASE);
    U8* MEMORY_READ_8;
    U16* MEMORY_READ_16;
    U8* MEMORY_WRITE_8;
    U16* MEMORY_WRITE_16;


} CPU_68K_MEMORY;

typedef enum CPU_68K_FLAGS 
{
    FLAG_S,
    FLAG_X,
    FLAG_Z,
    FLAG_N,
    FLAG_C,
    FLAG_V,
	FLAG_T0,
    FLAG_T1,
	FLAG_M

} CPU_68K_FLAGS;


#define 		M68K_REG_DA				CPU->DATA_REGISTER
#define			M68K_REG_D				CPU->DATA_REGISTER
#define			M68K_REG_A				(CPU->DATA_REGISTER + 8)
#define			M68K_REG_SR				CPU->STATUS_REGISTER
#define			M68K_REG_PPC			CPU->PREVIOUS_PC
#define			M68K_REG_PC				CPU->PC
#define			M68K_REG_SP				CPU->STACK_POINTER
#define			M68K_REG_USP			CPU->USER_STACK[0]
#define			M68K_REG_ISP			CPU->INTERRUPT_SP[4]
#define			M68K_REG_MSP			CPU->MASTER_SP[6]
#define			M68K_REG_SP_FULL		CPU->REGISTER_BASE[15]
#define			M68K_REG_VBR			CPU->VBR
#define			M68K_REG_SFC			CPU->SOURCE_FUNCTION_COUNTER
#define			M68K_REG_DFC			CPU->DEST_FUNCTION_COUNTER
#define			M68K_REG_CACR			CPU->CACHE_CONTROL
#define			M68K_REG_CAAR			CPU->CACHE_ADDRESS
#define			M68K_REG_IR				CPU->INDEX_REGISTER
#define 		M68K_REG_FPR			CPU->FPR
#define			M68K_REG_FPCR			CPU->FPCR
#define			M68K_REG_FPSR			CPU->FPSR
#define			M68K_REG_FPIAR			CPU->FPIAR

#define  		M68K_FLAG_T0			CPU->T0_FLAG
#define			M68K_FLAG_T1			CPU->T1_FLAG
#define			M68K_FLAG_S				CPU->S_FLAG
#define			M68K_FLAG_M				CPU->M_FLAG
#define			M68K_FLAG_X				CPU->X_FLAG
#define			M68K_FLAG_N				CPU->N_FLAG
#define			M68K_FLAG_Z				CPU->Z_FLAG
#define			M68K_FLAG_V				CPU->V_FLAG
#define			M68K_FLAG_C				CPU->C_FLAG
#define			M68K_FLAG_INT_LVL		CPU->INT_LEVEL
#define			M68K_CPU_STOPPED		CPU->CPU_STOPPED

#define			M68K_CYC_EXCE			CPU->CYCLE_EXCEPTION
#define 		M68K_CYCLE				CPU->INSTRUCTION_CYCLES[16]

#define         M68K_INT_ACK            CPU->INT_ACK_CALLBACK
#define         M68K_RESET_ACK          CPU->RESET_CALLBACK
#define         M68K_PC_CHANGED         CPU->PC_CHANGED_CALLBACK
#define         M68K_SET_FC_ACK         CPU->SET_FC_CALLBACK
#define         M68K_INSTR_HOOK         CPU->INSTR_HOOK


/*===============================================================================*/
/*							        68000 MISC.							         */
/*===============================================================================*/

extern CPU_68K* CPU;
extern CPU_68K_MEMORY* CPU_MEMORY;

#endif
#endif
