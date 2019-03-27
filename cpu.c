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



#include "./headers/include.h"
#include "./headers/define.h"



int
main(      int   argc,
     const char *argv[])
{
    uint8_t memory[ MAX ];         // Simulate computer RAM 
    uint8_t buffer[ QTD_ARG ];     // Separe file input in two parts

    INSTRUCTION format[ MAX ];     // Store instruction for fost execution

    /*
     *  Processor registers:
     *    stat -> Store carry, overflow and zero information about acc register.
     *    acc  -> The values of all logic and arithmetic sentences;
     *    pc   -> Where I should look for an instruction;
     */
    register uint8_t stat = 0;     // Status
    register uint8_t acc  = 0;     // Acumulator
    register uint8_t pc   = 0;     // Program Counter



    /*
     *  Open file and verify integrity.
     */
    FILE *program = fopen( argv[ 1 ], "rb" );

    if ( !program )
    {
        fprintf( stderr, "Error: Need to provide the file's name.\n" );
        return EXIT_FAILURE;
    }

    /*
     *  Store each instruction in a position of a struct
     */
    while ( fread( buffer, sizeof( uint8_t ), 1 << 1, program ) )
    {
        format[ pc ].opcode  = *(buffer);
        format[ pc ].operand = *(buffer + 1);



        /*
         *  Print debug line (on/off in "define.h")
         */
        DEBUG( printf( "DEBUG: opcode:%3d    operand:%3d\n", format[ pc ].opcode, format[ pc ].operand ); )



        pc++;
    }

    pc = 0;                // Restarting Program Counter register
    fclose( program );



    /*
     *  print assembly header (on/off in "define.h")
     */
    ASM_FILE( FILE *assembly = fopen( "./assemblies/GENERATED.asm", "w" );     )
    ASM_FILE( if ( !assembly )                                                 )
    ASM_FILE( {                                                                )
    ASM_FILE(     fprintf( stderr, "Error: Cannot generate assembly file\n" ); )
    ASM_FILE( }                                                                )
    ASM_FILE( fprintf( assembly, ";\t\tAssembly code\n\n" );                   )



    /*
     *  Processor loop:
     *    1 -> Store operation
     *    2 -> Increase Program Counter
     *    3 -> Execute operation (switch-case)
     */
    for ( EVER )
    {
        /*
         *  This operation is being executed at all switch-cases,
         *  so we can execute them here, to simplify our code.
         */
        uint8_t opcode  = format[ pc ].opcode;
        uint8_t operand = format[ pc ].operand;

        /*
         *  Increase program counter for next switch-case
         */
        pc++;

        switch ( opcode )
        {
            /*
             *     Code Format: load $address
             *  Operation Code: 00
             *      Definition: Loads the value of memory[ address ] in acc
             */
            case 0:
            {
                /*
                 *  print commented assembly line (on/off in "define.h")
                 */
                ASM_FILE( fprintf( assembly, "  load   $%3d ;   acc = %d\n", operand, acc ); )



                /*
                 *  Execute operation
                 */
                acc = memory[ operand ];


                /*
                 *  STAT
                 *
                 *  Order:
                 *    1 - Overflow
                 *    2 - Carry
                 *    3 - Zeroacc
                 */
                stat = stat & (UINT8_T - OVERFLOW);        // xxx - 0xx

                stat = stat & (UINT8_T - CARRY);           // xxx - x0x

                if ( acc == 0 )
                {
                    stat = stat | ZEROACC;                 // xxx - xx1
                }
                else
                {
                    stat = stat & (UINT8_T - ZEROACC);     // xxx - xx0
                }


                break;
            }


            /*
             *     Code Format: load 'number'
             *  Operation Code: 01
             *      Definition: Loads the value of 'number' in acc
             */
            case 1:
            {
                /*
                 *  print commented assembly line (on/off in "define.h")
                 */
                ASM_FILE( fprintf( assembly, "  load    %3d ;   acc = %d\n", operand, acc ); )
                


                /*
                 *  Execute operation
                 */
                acc = operand;


                /*
                 *  STAT
                 *
                 *  Order:
                 *    1 - Overflow
                 *    2 - Carry
                 *    3 - Zeroacc
                 */
                stat = stat & (UINT8_T - OVERFLOW);        // xxx - 0xx

                stat = stat & (UINT8_T - CARRY);           // xxx - x0x

                if ( acc == 0 )
                {
                    stat = stat | ZEROACC;                 // xxx - xx1
                }
                else
                {
                    stat = stat & (UINT8_T - ZEROACC);     // xxx - xx0
                }


                break;
            }


            /*
             *     Code Format: store $address
             *  Operation Code: 02
             *      Definition: Store the acc value in memory position defined by 'adress'
             */
            case 2:
            {
                /*
                 *  print commented assembly line (on/off in "define.h")
                 */
                ASM_FILE( fprintf( assembly, "  store  $%3d ;   memory[ %d ] = %d\n", operand, operand, acc ); )
                


                /*
                 *  Execute operation
                 */
                memory[ operand ] = acc;


                /*
                 *  STAT
                 *
                 *  Order:
                 *    1 - Overflow
                 *    2 - Carry
                 *    3 - Zeroacc
                 */
                stat = stat & (UINT8_T - OVERFLOW);        // xxx - 0xx

                stat = stat & (UINT8_T - CARRY);           // xxx - x0x

                if ( acc == 0 )
                {
                    stat = stat | ZEROACC;                 // xxx - xx1
                }
                else
                {
                    stat = stat & (UINT8_T - ZEROACC);     // xxx - xx0
                }


                break;
            }


            /*
             *     Code Format: add $address
             *  Operation Code: 03
             *      Definition: add the value in 'adress' position to acc
             */
            case 3:
            {
                /*
                 *  print commented assembly line (on/off in "define.h")
                 */
                ASM_FILE( fprintf( assembly, "  add    $%3d ;   acc = %d + %d\n", operand, acc, memory[ operand ] ); )



                /*
                 *  Execute operation
                 */
                short tmp = acc + memory[ operand ];


                /*
                 *  STAT
                 *
                 *  Order:
                 *    2 - Overflow
                 *    1 - Carry
                 *    3 - Zeroacc
                 */
                stat = stat & (UINT8_T - OVERFLOW);        // xxx - 0xx

                if ( tmp > UINT8_T )
                {
                    acc  = tmp  & UINT8_T;
                    stat = stat | CARRY;                   // xxx - x1x
                }
                else
                {
                    acc  = tmp;
                    stat = stat & (UINT8_T - CARRY);       // xxx - x0x
                }

                if ( acc == 0 )
                {
                    stat = stat | ZEROACC;                 // xxx - xx1
                }
                else
                {
                    stat = stat & (UINT8_T - ZEROACC);     // xxx - xx0
                }


                break;
            }


            /*
             *     Code Format: sub $address
             *  Operation Code: 04
             *      Definition: subtract the value in 'adress' position to acc
             */
            case 4:
            {
                /*
                 *  print commented assembly line (on/off in "define.h")
                 */
                ASM_FILE( fprintf( assembly, "  sub    $%3d ;   acc = %d - %d\n", operand, acc, memory[ operand ] ); )



                /*
                 *  Execute operation
                 */
                acc -= memory[ operand ];
                

                /*
                 *  STAT
                 *
                 *  Order:
                 *    1 - Overflow
                 *    2 - Carry
                 *    3 - Zeroacc
                 */
                stat = stat & (UINT8_T - OVERFLOW);        // xxx - 0xx

                stat = stat & (UINT8_T - CARRY);           // xxx - x0x

                if ( acc == 0 )
                {
                    stat = stat | ZEROACC;                 // xxx - xx1
                }
                else
                {
                    stat = stat & (UINT8_T - ZEROACC);     // xxx - xx0
                }


                break;
            }


            /*
             *     Code Format: mul $address
             *  Operation Code: 05
             *      Definition: multiply acc with the value in 'adress'
             */
            case 5:
            {
                /*
                 *  print commented assembly line (on/off in "define.h")
                 */
                ASM_FILE( fprintf( assembly, "  mul    $%3d ;   acc = %d * %d\n", operand, acc, memory[ operand ] ); )



                /*
                 *  Execute operation
                 */
                short tmp = acc * memory[ operand ];


                /*
                 *  STAT
                 *
                 *  Order:
                 *    1 - Overflow
                 *    2 - Carry
                 *    3 - Zeroacc
                 */
                if ( tmp > UINT8_T )
                {
                    acc  = tmp  & UINT8_T;
                    stat = stat | OVERFLOW;                 // xxx - 1xx
                }
                else
                {
                    acc  = tmp;
                    stat = stat & (UINT8_T - OVERFLOW);     // xxx - 0xx
                }

                stat = stat & (UINT8_T - CARRY);            // xxx - x0x

                if ( acc == 0 )
                {
                    stat = stat | ZEROACC;                  // xxx - xx1
                }
                else
                {
                    stat = stat & (UINT8_T - ZEROACC);      // xxx - xx0
                }


                break;
            }



            /*
             *     Code Format: div $address
             *  Operation Code: 06
             *      Definition: divide acc witn the value in 'adress'
             */
            case 6:
            {
                /*
                 *  print commented assembly line (on/off in "define.h")
                 */
                ASM_FILE( fprintf( assembly, "  div    $%3d ;   acc = %d / %d\n", operand, acc, memory[ operand ] ); )



                /*
                 *  Execute operation
                 */
                if ( memory[ operand ] == 0 )
                {
                    printf( "can't divide %d by 0", acc );
                    
                    break;
                }

                acc /= memory[ operand ];


                /*
                 *  STAT
                 *
                 *  Order:
                 *    1 - Overflow
                 *    2 - Carry
                 *    3 - Zeroacc
                 */
                stat = stat & (UINT8_T - OVERFLOW);        // xxx - 0xx

                stat = stat & (UINT8_T - CARRY);           // xxx - x0x

                if ( acc == 0 )
                {
                    stat = stat | ZEROACC;                 // xxx - xx1
                }
                else
                {
                    stat = stat & (UINT8_T - ZEROACC);     // xxx - xx0
                }


                break;
            }


            /*
             *     Code Format : inc
             *  Operation Code : 07
             *      Definition : increase in one unit acc
             */
            case 7:
            {
                /*
                 *  print commented assembly line (on/off in "define.h")
                 */
                ASM_FILE( fprintf( assembly, "  inc         ;   acc = %d + 1\n", acc ); )



                /*
                 *  Execute operation
                 */
                short tmp = acc + 1;


                /*
                 *  STAT
                 *
                 *  Order:
                 *    1 - Overflow
                 *    2 - Carry
                 *    3 - Zeroacc
                 */
                stat = stat & (UINT8_T - OVERFLOW);        // xxx - 0xx

                if ( tmp > UINT8_T )
                {
                    acc  = tmp  & UINT8_T;                 
                    stat = stat | CARRY;                   // xxx - x1x
                }
                else
                {
                    acc++;
                    stat = stat & (UINT8_T - CARRY);       // xxx - x0x
                }

                if ( acc == 0 )
                {
                    stat = stat | ZEROACC;                 // xxx - xx1
                }
                else
                {
                    stat = stat & (UINT8_T - ZEROACC);     // xxx - xx0
                }


                break;
            }


            /*
             *     Code Format: dec
             *  Operation Code: 08
             *      Definition: decrease in one unit acc
             */
            case 8:
            {
                /*
                 *  print commented assembly line (on/off in "define.h")
                 */
                ASM_FILE( fprintf( assembly, "  dec         ;   acc = %d - 1\n", acc ); )
                


                /*
                 *  Execute operation
                 */
                acc--;


                /*
                 *  STAT
                 *
                 *  Order:
                 *    1 - Overflow
                 *    2 - Carry
                 *    3 - Zeroacc
                 */
                stat = stat & (UINT8_T - OVERFLOW);        // xxx - 0xx

                stat = stat & (UINT8_T - CARRY);           // xxx - x0x

                if ( acc == 0 )
                {
                    stat = stat | ZEROACC;                 // xxx - xx1
                }
                else
                {
                    stat = stat & (UINT8_T - ZEROACC);     // xxx - xx0
                }


                break;
            }


            /*
             *     Code Format: and $adress
             *  Operation Code: 09
             *      Definition: acc = acc & mem[addr]
             */
            case 9:
            {
                /*
                 *  print commented assembly line (on/off in "define.h")
                 */
                ASM_FILE( fprintf( assembly, "  and    $%3d ;   acc = %d & %d\n", acc, operand ); )
                


                /*
                 *  Execute operation
                 */
                acc = acc & operand;


                /*
                 *  STAT
                 *
                 *  Order:
                 *    1 - Overflow
                 *    2 - Carry
                 *    3 - Zeroacc
                 */
                stat = stat & (UINT8_T - OVERFLOW);        // xxx - 0xx

                stat = stat & (UINT8_T - CARRY);           // xxx - x0x

                if ( acc == 0 )
                {
                    stat = stat | ZEROACC;                 // xxx - xx1
                }
                else
                {
                    stat = stat & (UINT8_T - ZEROACC);     // xxx - xx0
                }


                break;
            }


            /*
             *     Code Format: or $adress
             *  Operation Code: 10
             *      Definition: acc = acc | mem[addr]
             */
            case 10:
            {
                /*
                 *  print commented assembly line (on/off in "define.h")
                 */
                ASM_FILE( fprintf( assembly, "  or     $%3u ;   acc = %u | %u\n", acc, operand ); )



                /*
                 *  Execute operation
                 */
                acc = acc | memory[ operand ];


                /*
                 *  STAT
                 *
                 *  Order:
                 *    1 - Overflow
                 *    2 - Carry
                 *    3 - Zeroacc
                 */
                stat = stat & (UINT8_T - OVERFLOW);        // xxx - 0xx

                stat = stat & (UINT8_T - CARRY);           // xxx - x0x

                if ( acc == 0 )
                {
                    stat = stat | ZEROACC;                 // xxx - xx1
                }
                else
                {
                    stat = stat & (UINT8_T - ZEROACC);     // xxx - xx0
                }


                break;
            }


            /*
             *     Code Format: not $adress
             *  Operation Code: 11
             *      Definition: negate all bytes in 'adress'
             */
            case 11:
            {
                /*
                 *  print commented assembly line (on/off in "define.h")
                 */
                ASM_FILE( fprintf( assembly, "  not    $%3d ;   acc = %d\n", acc, operand ); )



                /*
                 *  Execute operation
                 */
                memory[ operand ] = ~memory[ operand ];


                /*
                 *  STAT
                 *
                 *  Order:
                 *    1 - Overflow
                 *    2 - Carry
                 *    3 - Zeroacc
                 */
                stat = stat & (UINT8_T - OVERFLOW);        // xxx - 0xx

                stat = stat & (UINT8_T - CARRY);           // xxx - x0x

                if ( acc == 0 )
                {
                    stat = stat | ZEROACC;                 // xxx - xx1
                }
                else
                {
                    stat = stat & (UINT8_T - ZEROACC);     // xxx - xx0
                }


                break;
            }


            /*
             *     Code Format: jmp #LABEL
             *  Operation Code: 12
             *      Definition: Go to 'LABEL'
             */
            case 12:
            {
                /*
                 *  print commented assembly line (on/off in "define.h")
                 */
                ASM_FILE( fprintf( assembly, "  jmp    L%3d ;   goto L%d\n", acc, acc ); )



                /*
                 *  Execute operation
                 */
                pc = operand / 2;


                /*
                 *  STAT
                 *
                 *  Order:
                 *    1 - Overflow
                 *    2 - Carry
                 *    3 - Zeroacc
                 */
                stat = stat & (UINT8_T - OVERFLOW);     // xxx - 0xx

                stat = stat & (UINT8_T - CARRY);        // xxx - x0x

                stat = stat & (UINT8_T - ZEROACC);      // xxx - xx0


                break;
            }


            /*
             *     Code Format: jz #LABEL
             *  Operation Code: 13
             *      Definition: if acc equals to 0, go to 'LABEL'
             */
            case 13:
            {
                /*
                 *  print commented assembly line (on/off in "define.h")
                 */
                ASM_FILE( fprintf( assembly, "  jz     L%3d ;   if == 0, goto L%d\n", acc, acc ); )



                /*
                 *  Execute operation
                 */
                if ( stat & ZEROACC )
                {
                    pc = operand / 2;
                }


                /*
                 *  STAT
                 *
                 *  Order:
                 *    1 - Overflow
                 *    2 - Carry
                 *    3 - Zeroacc
                 */
                stat = stat & (UINT8_T - OVERFLOW);     // xxx - 0xx

                stat = stat & (UINT8_T - CARRY);        // xxx - x0x

                stat = stat & (UINT8_T - ZEROACC);      // xxx - xx0


                break;
            }


            /*
             *     Code Format: jnz #LABEL
             *  Operation Code: 14
             *      Definition: if acc is not equal to 0, go to 'LABEL'
             */
            case 14:
            {
                /*
                 *  print commented assembly line (on/off in "define.h")
                 */
                ASM_FILE(  fprintf(assembly, "  jnz    L%3d ;   if != 0, goto L%d\n", acc, acc);  )



                /*
                 *  Execute operation
                 */
                if ( !( stat & ZEROACC ) )
                {
                    pc = operand / 2;
                }


                /*
                 *  STAT
                 *
                 *  Order:
                 *    1 - Overflow
                 *    2 - Carry
                 *    3 - Zeroacc
                 */
                stat = stat & (UINT8_T - OVERFLOW);     // xxx - 0xx

                stat = stat & (UINT8_T - CARRY);        // xxx - x0x

                stat = stat & (UINT8_T - ZEROACC);      // xxx - xx0


                break;
            }


            /*
             *     Code Format: hlt
             *  Operation Code: 15
             *      Definition: end program (return 0)
             */
            case 15:
            {
                ASM_FILE( fprintf( assembly, "  hlt         ;   End of program\n" ); )
                ASM_FILE( fclose( assembly ); )


                goto SHUTDOWN;
            }


            /*
             *  In rare cases when the command is not allowed
             */
            default:
            {
                break;
            }
        }
    }

SHUTDOWN:


    printf( "  acc: %3d\n", acc );
    printf( " stat: %3d\n", stat );


    return EXIT_SUCCESS;
}