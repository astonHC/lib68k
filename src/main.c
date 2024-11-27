/* COPYRIHGT (C) HARRY CLARK 2024 */

/* MOTOROLA 68000 STANDALONE EMULATION LIBRARY */

/* THIS FILE PERTAINS TOWARDS THE MAIN FUNCTIONALITY OF THE PROGRAM */

/* NESTED INCLUDES */

#include "util.h"
#include "68K.h"
#include "68KOPCODE.h"

static LIB_BASE* LIB68K;

#define         PC_MAX_VALUE            0x10000
#define         M68K_REG_NUM            0

int main(int argc, char** argv)
{
    printf("HARRY CLARK - MOTOROLA 680x0 EMULATOR\n");
    
    if(argc < 1)
    {
        char* INDEX;
        strncpy(LIB68K->OUTPUT_PATH, argv[1], sizeof(LIB68K->OUTPUT_PATH));

        // RETURNS A NEW OCCRUANCE OF A NEW LINE CHARACTER TO DENOTE THE OUTPUT PATH

        for(INDEX = strchr(LIB68K->OUTPUT_PATH, '\\'); INDEX; INDEX = strchr(INDEX, '\\'))
        {
            *INDEX = '/';
        }

        // EVALUATE THE LENGTH OF THE NEW OUTPUT PATH OF THE FILE INPUT

        if(LIB68K->OUTPUT_PATH[strlen(LIB68K->OUTPUT_PATH) - 1 ] != '/') 
        {
            
        }
    }

    printf("Initialising 68000\n");
    M68K_INIT();
    M68K_EXEC();
    printf("68000 is running: %p\n", (void*)&CPU);


    printf("Setting 68K Program Counter\n");
    M68K_SET_REGISTERS(M68K_REG_PC, PC_MAX_VALUE);   
    printf("68K Program Counter defined with Value: %d\n", PC_MAX_VALUE);

    printf("====================================================\n");

    printf("Setting 68K Data Register\n");
    M68K_GET_REGISTERS(&CPU, M68K_REG_D[M68K_REG_NUM]);
    printf("68K Data Register 0x%d Set\n", M68K_REG_NUM);


    return 0;
 
}
