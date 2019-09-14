#ifndef CPU_H_
# define CPU_H_

# include "include.h"
# include "define.h"



void  cpu  ( INSTRUCTION *format
# ifdef ASM_FILE
           , FILE        *assembly
# endif
);



#endif    // CPU_H_
