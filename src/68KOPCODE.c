/* COPYRIHGT (C) HARRY CLARK 2024 */

/* MOTOROLA 68000 STANDALONE EMULATION LIBRARY */

/* THIS FILE ACTS AS AN EXPANSION OF THE PRE-REQUISTIES DEFINED IN THE MAIN CPU HEADER */
/* PROVIDING MOODULARISATION AND CROSS COMPILATION FOR OPCODE RELATED HANDLERS */

/* NESTED INCLUDES */

#include "68KOPCODE.h"

#ifdef BUILD_OP_TABLE

/* EXCEPTION HANDLER FOR A-LINE INSTRUCTION HANDLERS */
/* DISCERN THE CURRENT EXCEPTION BEING FED INTO PC AND APPEND THAT THROUGH A JMP */ 

void M68K_OP_1010(void)
{
    M68K_SET_FUNC_CALLBACK(M68K_REG_PC);
    M68K_JUMP_VECTOR(M68K_EXCEPTION_1010);

    /* USE THE INTEGREAL POINTER NOTATION TO ACCESS THE EXCEPTION FROM THE CURRENT A-LINE INSTRUCTION */
    /* PROVIDE ACCESS TO THE INDEX REGISTER */

    M68K_USE_CYCLES(M68K_CYC_EXCE[M68K_EXCEPTION_1010] - (M68K_CYC_EXCE[*M68K_REG_IR]));
}

/* SAME THING BUT FOR F-LINE INSTRUCTION HANDLERS */

void M68K_OP_1111(void)
{
    M68K_SET_FUNC_CALLBACK(M68K_REG_PC);
    M68K_JUMP_VECTOR(M68K_EXCEPTION_1111);

    M68K_USE_CYCLES(M68K_CYC_EXCE[M68K_EXCEPTION_1111] - (M68K_CYC_EXCE[*M68K_REG_IR]));

}

/* THE FOLLOWING WILL REFER TO THE BITWISE MEANS BY WHICH ALL OF THESE OPCODES OPERATE */
/* ALL OF THE SUBSEQUENT INFORMATION CAN BE SOURED FROM: https://www.nxp.com/docs/en/reference-manual/M68000PRM.pdf */

/* FORTUNTATELY, THERE IS A LOT OF INFORMATION PERTAINING TOWARDS HOW EVERYTHING WORKS IN THE DESC */
/* THERE IS A LOT OF NUANCE WITH THESE INSTRUCTIONS - SO THE ORDER OF OPERATIONS WILL VARY */

/* THE GENERAL JYST IS WORKING WITH POINTERS BETWEEN A SOURCE AND A DESTINATION */

/* SEE INTEGER INSTRUCTIONS: https://www.nxp.com/docs/en/reference-manual/M68000PRM.pdf#PAGE=105 */

void M68K_OP_ABCD_BYTE(void)
{
    int DESTINATION = M68K_DATA_HIGH;
    int SRC = M68K_DATA_LOW;

    /* THERE *MUST* BE AN EASIER WAY OF DEFINING THE POSITION AND LOCATION OF OPERANDS */
    /* THIS IS VERY SCUFFED AT THE MOMENT, SO BARE WITH ME AS I IRON THIS OUT, THIS DOES NOT SEEM RIGHT */

    /* WHAT THIS IS DOING IS READING THE LOW DATA SECTION WITH THE SRC OPERAND, DESTINATION BASED OF THE EXTEND FLAG */
    /* THE EXTEND FLAG GOVERNS THE BASIS OF SETTING THE SAME BIT CURRENTLY IN THE OPERATION TO THE CARRY BIT (CARRY TO DEST) */

    int RESULT = *((int*)M68K_LOW_NIBBLE(SRC) + M68K_LOW_NIBBLE(DESTINATION) + M68K_FLAG_X) >> DESTINATION;

    /* IF THE DATA IS OUT OF THE LOW NIBBLE RANGE (0 - 8) */

    if(RESULT > 9)
    {
        RESULT += M68K_HIGH_NIBBLE(SRC) + M68K_HIGH_NIBBLE(DESTINATION);
    }

    M68K_FLAG_V += M68K_HIGH_NIBBLE(SRC) + M68K_HIGH_NIBBLE(DESTINATION);
    DESTINATION = M68K_MASK_OUT_ABOVE_8(DESTINATION) | RESULT;
}   


#endif
