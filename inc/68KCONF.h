/* COPYRIHGT (C) HARRY CLARK 2024 */

/* MOTOROLA 68000 STANDALONE EMULATION LIBRARY */

/* THIS FILE PERTAINS TOWARDSS THE MAIN FUNCTIONALITY SURROUNDING THE CONFIGURATION */
/* OF EACH RESPECTIVE CPU'S TYPE AND RELATIVE HANDLERS */ 

#ifndef M68K_CONFIG
#define M68K_CONFIG

/* NESTED INCLUDES */

#include "common.h"

/*===============================================================================*/
/*							68000 DEBUG											 */
/*===============================================================================*/

/* MISCALLANEOUS TYPES FOR A LINE EXCEPTION HANDLERS */
/* THIS WILL BE USED IN DOCUMENTING CYCLE ACCURATE EXCEPTIONS AT RUNTIME */

#if M68K_LOG_ENABLE
	extern FILE* M68K_LOG_FILEHANDLE
	#define M68K_DO_LOG(A) 			if(M68K_LOG_FILEHANDLE) 
	#if M68K_LOG_1010_1111_A_LINE
		#define M68K_DO_LOG(A) 		if(M68K_LOG_FILEHANDLE) fprintf(stdout, A)
	#else
		#define M68K_DO_LOG_EMU(A)
	#endif
#else
	#define M68K_DO_LOG(A)
	#define M68K_DO_LOG_EMU(A)

	/* OPTIONS FOR IMMEDIATE ADDRESSING DIRECTIVES WHEN LOOKING */
	/* FOR CPU CALLBACKS */	

	#define M68K_OPT_OFF				0
	#define M68K_OPT_ON					1

#endif

#ifdef USE_CYCLES
#define USE_CYCLES
#else

#define 	M68K_ADD_CYCLES(VALUE)				(*(int*)M68K_CYC_REMAIN) += (VALUE)
#define		M68K_USE_CYCLES(VALUE)				(*(int*)M68K_CYC_REMAIN) -= (VALUE)
#define		M68K_SET_CYCLES(VALUE)				(*(int*)M68K_CYC_REMAIN) = VALUE
#define		M68K_GET_CYCLES()					(*(int*)M68K_CYC_REMAIN)
#define		M68K_ALL_CYCLES()					(*(int*)M68K_CYC_REMAIN) %= M68K_CYCLE[M68K_REG_IR]

#endif


#define 	M68K_MASK_OUT_ABOVE_8(A)            ((A) & 0xFF)
#define 	M68K_MASK_OUT_ABOVE_16(A)           ((A) & 0xFFFF)
#define 	M68K_MASK_OUT_ABOVE_32(A)           ((A) & 0xFFFFFFF)
#define     M68K_RETURN_ADDRESS(ADDRESS)        ((*ADDRESS) & 0xFFFFFFFFFF)

/*===============================================================================*/
/*							68000 CALLBACKS						     			 */
/*===============================================================================*/


int M68K_SET_INT_CALLBACK(int* LEVEL);
void M68K_DEFAULT_INSTR_CALLBACK(void);
void M68K_SET_FUNC_CALLBACK(int* CALLBACK);
void M68K_SET_INSTR_CALLBACK(void(*CALLBACK), unsigned PC);
void M68K_SET_MOVE_IRQ_INT(void);
U16 M68K_FETCH_INSTR();

/*===============================================================================*/
/*							68000 READ AND WRITE							     */
/*===============================================================================*/


extern unsigned int M68K_READ_8(unsigned int ADDRESS);
extern unsigned int M68K_READ_16(unsigned int ADDRESS);
extern unsigned int M68K_READ_32(unsigned int ADDRESS);

extern void M68K_WRITE_8(unsigned int ADDRESS, unsigned int DATA);
extern void M68K_WRITE_16(unsigned int ADDRESS, unsigned int DATA);
extern void M68K_WRITE_32(unsigned int ADDRESS, unsigned int DATA);

extern unsigned int CTRL_READ_BYTE(unsigned int ADDRESS);
extern unsigned int CTRL_READ_WORD(unsigned int ADDRESS);
extern void CTRL_WRITE_BYTE(unsigned int ADDRESS, unsigned int DATA);
extern void CTRL_WRITE_WORD(unsigned int ADDRESS, unsigned int DATA);

void M68K_SET_CPU_TYPE(unsigned TYPE);


#endif
