/******************************************************************************************************
 ******************************************************************************************************
 *****                                                                                            *****
 *****                                  Engenharia de Computação                                  *****
 *****                                                                                            *****
 *****                                         SP1 Emulator                                       *****
 *****                                        Version 0.0.1                                       *****
 *****                                                                                            *****
 *****                                       Vinícius Aguiar                                      *****
 *****                                                                                            *****
 *****                                   26.02.2019 - 28.03.2019                                  *****
 *****                                                                                            *****
 ******************************************************************************************************
 ******************************************************************************************************/


#ifndef DEFINE_H_
# define DEFINE_H_


/*
 *  Macros
 */
# define MAX            1 << 8
# define QTD_ARG        1 << 1

# define EVER               ;;

# define UINT8_T           255
# define OVERFLOW            4     
# define CARRY               2     
# define ZEROACC             1

/*
 * Debug and .asn generator
 */
# define DEBUG(x)           // x
# define ASM_FILE(x)        // x


/*
 *  Input store
 */
typedef struct format
{
    uint8_t operand;     // Identifier  -> 0000 0000 (0) to 1111 1111 (255)
    uint8_t opcode;      // Instruction -> 0000 0000 (0) to 0000 1111  (15)
} INSTRUCTION;



#endif     // DEFINE_H_
