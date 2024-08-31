/* COPYRIHGT (C) HARRY CLARK 2024 */

/* MOTOROLA 68000 STANDALONE EMULATION LIBRARY */

/* THIS FILE PERTAINS TOWARDSS THE MAIN FUNCTIONALITY SURROUNDING THE UTILITY */
/* OF THE CPU AND IT'S SUBSEQUENT DIRECTIVES AND DEFINES */

/* ANY AND ALL OF THE CORRESPONDING DEFINES AND DECLARATIONS CAN BE */
/* ATTRIBUTED TO THE INFROMATION FOUND HERE: https://www.nxp.com/docs/en/reference-manual/M68000PRM.pdf  */ 

/* NESTED INCLUDES */

#include "68K.h"
#include "68KCONF.h"
#include "common.h"

#ifndef USE_68K

/*===============================================================================*/
/*							68000 MAIN CPU FUNCTIONALIY							 */
/*===============================================================================*/

/* FOLLOWING THE INITIAL DECLARATION OF THE VECTOR TABLE */
/* DISCERN THE RUDIMENTARY AMOUNT OF CPU CYCLES */
/* THE CPU WILL GOVERN OVER THE COURSE OF IT'S RUN TIME */

/* THIS WILL ENCOMPASS THE WIDE BITWISE VARIETY */
/* THROUGH THE MEANS OF EVALUATING THE SIZE OF THE DESIGNATED MEMORY */

/* SEE 1.1 USER PROGRAMMING MODEL https://www.nxp.com/docs/en/reference-manual/M68000PRM.pdf#page=13 */

void INITIALISE_68K_CYCLES(void)
{
	char* CPU_68K_CYCLES = (char*)malloc(sizeof((char)M68K_BASE_BITMASK));

	/* THIS LOOP WILL CHECK FOR EVERY SUBSEQUENT BITWISE */
	/* OPERATION AND EVALUATE IT'S DESIGNATED MEMORY */

	/* THE FIRST CO-EFFICIENT REPRESENTS THE BITWISE LENGTH OF THE OPERATION */
	/* THE SECOND CO-EFFICIENT REPRESENTS THE SIZE OF THE REGISTER */

	for (size_t INDEX = 0; INDEX < sizeof(CPU_68K_CYCLES); INDEX++)
	{	
		switch (INDEX / 16)
		{
			case 0:
				CPU_68K_CYCLES[INDEX] += (int)M68K_LOW_BITMASK;
				break;

			case 1:
				CPU_68K_CYCLES[INDEX] += (int)M68K_MID_BITMASK;
				break;

			case 2:
				CPU_68K_CYCLES[INDEX] += (int)M68K_HIGH_BITMASK;
				break;

			default:
				CPU_68K_CYCLES[INDEX] += (int)M68K_MAX_BITMASK;
				break;
		}
	}
}

/* ACCESS EACH RESPECTIVE REGISTER FROM THE ENUMERATION */
/* RETURN THE CORRESPONDENCE IN RELATION TO THE SIZE */

/* FOR EASE OF USE WHEN ACCESSING METHODS, I HAVE CREATED A MACRO */
/* TO BE ABLE TO RETURN THE CORRESPONDING ADDRESS VALUE IN RELATION */
/* TO THE INDEXXING OF THE REGISTER ARRAY */

U32* M68K_GET_REGISTERS(struct CPU_68K* CPU, int REGISTER)
{
    /* IF THERE IS NO ACCESSIBLE METHODS */
	/* WE SPECIFICALLY ALLOCATE MEMORY SAID ACCESSING OF REGISTERS */

	/* THE REASON AS TO WHY THERE ARE TWO SEPERATE CASTS IS DUE TO THE FACT */
	/* THAT THE UINTPTR WILL HOUSE THE CORRESPONDING POINTER OF THE RESPECTIVE 32 BIT INTEGER */

	/* IT HAS NOW BEEN UPDATED TO ACCOMODATE FOR THE ACTUAL RETURN OF A 32 BIT INT */
	/* AKIN TO THE MAX SIZE OF THE REGISTERS */

	switch(REGISTER)
	{
		case M68K_D0: return CPU->REGISTER_BASE[0];
		case M68K_D1: return CPU->REGISTER_BASE[1];
		case M68K_D2: return CPU->REGISTER_BASE[2];
		case M68K_D3: return CPU->REGISTER_BASE[3];
		case M68K_D4: return CPU->REGISTER_BASE[4];
		case M68K_D5: return CPU->REGISTER_BASE[5];
		case M68K_D6: return CPU->REGISTER_BASE[6];
		case M68K_D7: return CPU->REGISTER_BASE[7];
		
		case M68K_A0: return CPU->REGISTER_BASE[8];
		case M68K_A1: return CPU->REGISTER_BASE[9];
		case M68K_A2: return CPU->REGISTER_BASE[10];
		case M68K_A3: return CPU->REGISTER_BASE[11];
		case M68K_A4: return CPU->REGISTER_BASE[12];
		case M68K_A5: return CPU->REGISTER_BASE[13];
		case M68K_A6: return CPU->REGISTER_BASE[14];
		case M68K_A7: return CPU->REGISTER_BASE[15];

        case M68K_PC: return (U32*)(uintptr_t)M68K_RETURN_ADDRESS(CPU->PC);

		case M68K_USP:
			return (unsigned*)CPU->S_FLAG;

		case M68K_ISP:
            return CPU->S_FLAG ? (U32*)CPU->STACK_POINTER[4] : (U32*)CPU->REGISTER_BASE[15];

		case M68K_SP:
			return CPU->REGISTER_BASE[15];

		case M68K_SFC:
			return CPU->SOURCE_FUNCTION_COUNTER;

		case M68K_DFC:
			return CPU->DEST_FUNCTION_COUNTER;

		case M68K_VBR:
			return CPU->VBR;

		case M68K_CACR:
			return CPU->CACHE_CONTROL;

		case M68K_CAAR:
			return CPU->CACHE_ADDRESS;

		case M68K_IR:
			return CPU->INDEX_REGISTER;

		default:
			return NULL;
	}
}

/* IN A SIMILAR VEIN TO THE FUNCTION ABOVE, THIS FUNCTION WILL FOCUS MOREOVER */
/* ON THE SETTING OF THESE VALUES */

/* THIS IS POSSIBLE DUE TO THE WAY IN WHICH THE ENUM VALUES ARE ASSIGNED TO THE SPECIFIC */
/* MACRO WITH AN ALLOCATED SIZE */

void M68K_SET_REGISTERS(int REGISTER, unsigned VALUE)
{
	switch (REGISTER)
	{
		case M68K_D0: M68K_REG_D[0] += M68K_MASK_OUT_ABOVE_32(VALUE); 
		case M68K_D1: M68K_REG_D[1] += M68K_MASK_OUT_ABOVE_32(VALUE);
		case M68K_D2: M68K_REG_D[2] += M68K_MASK_OUT_ABOVE_32(VALUE); 
		case M68K_D3: M68K_REG_D[3] += M68K_MASK_OUT_ABOVE_32(VALUE); 
		case M68K_D4: M68K_REG_D[4] += M68K_MASK_OUT_ABOVE_32(VALUE); 
		case M68K_D5: M68K_REG_D[5] += M68K_MASK_OUT_ABOVE_32(VALUE); 
		case M68K_D6: M68K_REG_D[6] += M68K_MASK_OUT_ABOVE_32(VALUE); 
		case M68K_D7: M68K_REG_D[7] += M68K_MASK_OUT_ABOVE_32(VALUE); 

		case M68K_A0: M68K_REG_A[8] += M68K_MASK_OUT_ABOVE_32(VALUE); 
		case M68K_A1: M68K_REG_A[9] += M68K_MASK_OUT_ABOVE_32(VALUE); 
		case M68K_A2: M68K_REG_A[10] += M68K_MASK_OUT_ABOVE_32(VALUE); 
		case M68K_A3: M68K_REG_A[11] += M68K_MASK_OUT_ABOVE_32(VALUE); 
		case M68K_A4: M68K_REG_A[12] += M68K_MASK_OUT_ABOVE_32(VALUE); 
		case M68K_A5: M68K_REG_A[13] += M68K_MASK_OUT_ABOVE_32(VALUE); 
		case M68K_A6: M68K_REG_A[14] += M68K_MASK_OUT_ABOVE_32(VALUE); 
		case M68K_A7: M68K_REG_A[15] += M68K_MASK_OUT_ABOVE_32(VALUE); 

		case M68K_PC: M68K_JUMP(M68K_MASK_OUT_ABOVE_32(VALUE)); 
		case M68K_SR: M68K_SET_SR_IRQ(VALUE); 
		case M68K_SP: M68K_REG_SP[7] = M68K_MASK_OUT_ABOVE_32(VALUE); 

		case M68K_USP: 
				if(FLAG_S) M68K_REG_USP = M68K_MASK_OUT_ABOVE_32(VALUE);
					else
				M68K_REG_SP = (U32*)M68K_MASK_OUT_ABOVE_32(VALUE);

		case M68K_ISP:
				if(FLAG_S && !FLAG_M) M68K_REG_SP = (U32*)M68K_MASK_OUT_ABOVE_32(VALUE);
					else
				M68K_REG_ISP = M68K_MASK_OUT_ABOVE_32(VALUE);
	}
}

/*===============================================================================*/
/*									68000 CALLBACKS							     */
/*===============================================================================*/

/* THE FOLLOWING ARE A BUNCH OF ARBITRARY CALLBACKS PERTAINING TOWARDS THE CPU */

/* INTIALISE THE INTEGER TYPE CALLBACK */
/* THIS CALLBACK REFERS TO THE WAY IN WHICH THE DESIGNATED TYPE */
/* IS ABLE TO COMMUNICATE BETWEEN ALL AREAS OF EACH RESPECTIVE REGISTER */

/* SEE: https://www.nxp.com/docs/en/reference-manual/M68000PRM.pdf#page=14 */

/* ALLOCATE A DESIGNATED CHUNK OF MEMORY ASSUMING THE NOTION */
/* THAT THE RESPECTIVE REGISTER NEEDS TO ACCESS VALUES OF THIS ASSOCIATION */

#undef M68K_CPU_ARGS

int M68K_DEFAULT_INT_CALLBACK;
int M68K_SET_INT_CALLBACK(int* LEVEL)
{
	M68K_DEFAULT_INT_CALLBACK += *(U32*)LEVEL;
	M68K_FLAG_INT_LVL = 0;
	return *M68K_REG_VBR;
}

/* FOLLOWING ON FROM THE SAME PRINCIPLES AS ABOVE */
/* INITIALISE THE REMAINING CALLBACKS */

unsigned M68K_DEFAULT_FC_CALLBACK;
void M68K_SET_FUNC_CALLBACK(unsigned* CALLBACK)
{
	M68K_DEFAULT_FC_CALLBACK = *(U32*)CALLBACK;
}

/* DETERMINE THE STEP LATENCY OF RELEVANT MOVE BASED INSTRUCTIONS */
/* THIS CHECKS THE MASK TO PROCESS SAID IRQ */

void M68K_SET_MOVE_IRQ_INT()
{
	/* WE FIRST ASSERT THE RELATIVE SIZE NEEDED FOR EACH EXECUTION */
	/* OF THE PC AND INDEX REGISTER, IN ORDER TO COMPUTE THE CHANGE */

	/* DETERMINE THE CURRENT INT LEVEL AND BIT SHIFT IN LE FOR EACH DATA REGISTER */ 

	M68K_REG_PC = (U32*)M68K_ADDRESS_WIDTH_32;
	M68K_REG_IR += (U16)M68K_FETCH_INSTR(); 

	int INT_LEVEL = 0;

	INT_LEVEL &= 8;
}

unsigned int M68K_INSTR_CALLBACK;
void M68K_SET_INSTR_CALLBACK(void(*CALLBACK), unsigned PC)
{
	M68K_INSTR_CALLBACK += *(int*)CALLBACK &= PC;
}

/* DEFINE THE BASE JUMP COROUTINE TO BE ABLE TO DISCERN */
/* AS AND WHEN A NEW CONDITION IS RECOGNISED */ 

void M68K_JUMP(unsigned NEW_PC)
{
	M68K_REG_PC += (int)NEW_PC;
}

void M68K_JUMP_VECTOR(unsigned VECTOR)
{
	M68K_REG_PC += M68K_READ_32(VECTOR << 2);
}

/* PERFORM A LOGICAL BITWIS AND FROM THE SOURCE DESTINATION */
/* BEING THE VALUE OF THE CURRENT STATUS REGISTER INTERRUPT */
/* STORE THE RESULT IN THE TRACE REGISTERS */

/* SEE: https://www.nxp.com/docs/en/reference-manual/M68000PRM.pdf#page=119 */

void M68K_SET_SR_IRQ(unsigned VALUE)
{
	VALUE &= (int)M68K_SR_MASK;
	M68K_FLAG_T1 += ((S8)VALUE);
}

void M68K_INIT(void)
{
	M68K_BUILD_OPCODE_TABLE();
	M68K_SET_INT_CALLBACK(NULL);
	M68K_SET_FUNC_CALLBACK(NULL);
	M68K_SET_INSTR_CALLBACK(NULL, 0);
	M68K_SET_MOVE_IRQ_INT();
}

#endif
