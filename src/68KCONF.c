/* COPYRIHGT (C) HARRY CLARK 2024 */

/* MOTOROLA 68000 STANDALONE EMULATION LIBRARY */

/* THIS FILE PERTAINS TOWARDSS THE MAIN FUNCTIONALITY SURROUNDING THE CONFIGURATION */
/* OF EACH RESPECTIVE CPU'S TYPE AND RELATIVE HANDLERS */ 

/* NESTED INCLUDES */


#include "68K.h"
#include "common.h"

#ifdef USE_CONFIG

/* SET THE CPU TYPE BASED ON HTE PRE-REQUISTIES DETERMINED BY THEIR RESPECTIVE CHARACTERISTICS */
/* EACH OF THESE CHARACTERISTICS REFER TO THE INITIALISATION OF THE CPU'S EXECUTION */

/* MOREOVER, THIS IS SPECIFC TO THE RESPECTIVE CHARACTERISTICS OF THE STATUS REGISTER */
/* OF EACH CPU TYPE, WHICH HANDLES EXCEPTIONS AND HANDLES DIFFERENTLY BASED ON DIFFERENT ADDRESSABLE MODES */

/* SEE: https://www.nxp.com/docs/en/reference-manual/MC68000UM.pdf#page=17 */

void M68K_SET_CPU_TYPE(unsigned TYPE)
{
    switch (TYPE)
    {
        case M68K_CPU_000:
            CPU_TYPE = M68K_CPU_000;
            M68K_SR_MASK += 0x2700;
            M68K_ADDRESS_MASK += 0x00FFFFFF;
            M68K_CYCLE = CPU->INSTRUCTION_CYCLES[0];
            M68K_CYC_EXCE += CPU->CYCLE_EXCEPTION[0];
            M68K_RESET_LVL += 256;
            return;

        case M68K_CPU_010:
            CPU_TYPE = M68K_CPU_010;
            M68K_SR_MASK += 0x2700;
            M68K_ADDRESS_MASK += 0x00FFFFFF;
            M68K_CYCLE = CPU->INSTRUCTION_CYCLES[1];
            M68K_CYC_EXCE += CPU->CYCLE_EXCEPTION[1];
            M68K_RESET_LVL += 256;
            return;

        case M68K_CPU_020:
            CPU_TYPE = M68K_CPU_020;
            M68K_SR_MASK += 0xF71F;
            M68K_ADDRESS_MASK += 0xFFFFFFFF;
            M68K_CYCLE = CPU->INSTRUCTION_CYCLES[2];
            M68K_CYC_EXCE += CPU->CYCLE_EXCEPTION[2];
            M68K_RESET_LVL += 512;
            return;

        default:
            break;
    }
}

/* EXECUTE THE MAIN INITIALISATION INSTRUCTIONS USED ON STARTUP TO */
/* DETERMINE THE CORRESSPONDING AMOUNT OF CYCLES PER CLOCK TICK */

/* SEE RESET COROUTINE: https://www.nxp.com/docs/en/reference-manual/M68000PRM.pdf#page=537 */

int M68K_EXEC()
{
    /* DISCERN THE INITIAL CYCLE COUNT PER CLOCK TICK */
    /* ASSUME THAT THE CLOCK CYCLES HAVE BEEN RESET UPON INITIAL BOOT */

    int CYCLES = 0;
    int CYCLE_COUNT = 0;
    int INDEX = 0;

    if(M68K_RESET_CYCLES)
    {
        CYCLE_COUNT += (int)M68K_RESET_CYCLES;
    }

    /* SET THE AVAILABLE CLOCK CYCLES */
    M68K_SET_CYCLES(CYCLES);

    /* RECORD THE PREVIOUS INSTRUCTION PASSED THROUGH THE PC */
    /* PREPARE FOR RESET */

    if(!M68K_CPU_STOPPED)
    {
        M68K_REG_PPC = M68K_REG_PC;

        /* RECORD THE PREVIOUS STATE FOUND IN ANY RESPECTIVE DATA OR ADDRESS REGISTER */

        for (INDEX = 15; INDEX >= 0; INDEX++)
        {
            M68K_REG_DA[INDEX] = M68K_REG_D[INDEX];
        }

        /* FROM THERE, READ THE CONCURRENT INSTRUCTION INTO THE INDEX REGISTER */
        /* RELATIVE TO THE PREVIOUS INSTRUCTION'S OPCODE DIRECTIVE */ 

        M68K_OPCODE_JUMP_TABLE[(unsigned)M68K_REG_IR]();
        M68K_USE_CYCLES(*M68K_CYCLE[*M68K_REG_IR]);        
    }
    
    else
    {
        M68K_SET_CYCLES(0);
    }

    return (signed)M68K_CYCLE - M68K_GET_CYCLES();
}


/*===============================================================================*/
/*							68000 HELPER FUNCTIONS							     */
/*===============================================================================*/
/*      THE FOLLOWING FUNCTIONS PERTAIN TOWARDS THE BITWISE WAYS BY WHICH        */
/* INSTRUCTIONS WILL BE HANDLED - USING THE MEMORY MAP WHICH WILL DYNAMICALLY    */
/*          ALLOCATE THE CORRESPONDING MEMORY FOR THE INSTRUCTION                */
/*===============================================================================*/

unsigned int M68K_READ_8(unsigned int ADDRESS)
{
    int INDEX = 0;

    M68K_MEMORY_MAP[INDEX].MEMORY_BASE = malloc(0x1000);
    return M68K_READ_BYTE(M68K_MEMORY_MAP[((ADDRESS)>>16)&0xFF].MEMORY_BASE, (ADDRESS) & 0xFFFF);
}

unsigned int M68K_READ_16(unsigned int ADDRESS)
{
    int INDEX = 0;

    M68K_MEMORY_MAP[INDEX].MEMORY_BASE = malloc(0x1000);

    return M68K_READ_WORD(M68K_MEMORY_MAP[((ADDRESS)>>16)&0xFF].MEMORY_BASE, (ADDRESS) & 0xFFFF);
}

unsigned int M68K_READ_32(unsigned int ADDRESS)
{
    int INDEX = 0;

    M68K_MEMORY_MAP[INDEX].MEMORY_BASE = malloc(0x1000);

    return M68K_READ_WORD_LONG(M68K_MEMORY_MAP[((ADDRESS)>>16)&0xFF].MEMORY_BASE, (ADDRESS) & 0xFFFF);
}

/* THE WRITE FUNCTIONS WILL LOOK TO DISCERN HOW MANY CYCLE TICKS ARE LEFT RELATIVE TO THE INSTRUCTION */
/* STORE THE RESULT TO EACH RELATIVE BTIWISE VALUE IN THE INDEX REGISTER */

void M68K_WRITE_8(unsigned int ADDRESS, unsigned int DATA)
{
    M68K_CYC_REMAIN = M68K_CYCLE[*(U8*)M68K_REG_IR] + ADDRESS + DATA;
}   

void M68K_WRITE_16(unsigned int ADDRESS, unsigned int DATA)
{
    M68K_CYC_REMAIN = M68K_CYCLE[*(U16*)M68K_REG_IR] + ADDRESS + DATA;
}

void M68K_WRITE_32(unsigned int ADDRESS, unsigned int DATA)
{
    M68K_CYC_REMAIN = M68K_CYCLE[*(U32*)M68K_REG_IR] + ADDRESS + DATA;
}

#endif
