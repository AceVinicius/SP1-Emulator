#ifndef DEFINE_H_
# define DEFINE_H_



/*
 *  Macros
 */
# define MAX            1 << 8
# define QTD_ARG        1 << 1

# define OVERFLOW            4     
# define CARRY               2     
# define ZEROACC             1
# define OK                  0

/*
 * Debug and .asm generator
 */
// # define DEBUG
# define ASM_FILE

/*
 * Typedefs
 */
typedef uint8_t byte;

typedef struct format
{
    byte operand;     // Identifier  -> 0b00000000 (0) to 0b11111111 (255)
    byte opcode;      // Instruction -> 0b00000000 (0) to 0b00001111  (15)
}
INSTRUCTION;



#endif    // DEFINE_H_
