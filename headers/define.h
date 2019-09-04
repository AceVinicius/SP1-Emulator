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
# define DEBUG(x)          //  x
# define ASM_FILE(x)         x


typedef uint8_t byte;



#endif     // DEFINE_H_
