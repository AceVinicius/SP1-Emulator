# include "./../lib/include/include.h"
# include "./../lib/include/define.h"
# include "./../lib/include/stat.h"
# include "./../lib/include/cpu.h"


    
void
cpu( INSTRUCTION *format
#ifdef ASM_FILE
   , FILE        *assembly
#endif
                           )
{
    /*
     *  Processor registers:
     *    stat -> Store carry, overflow and zero information about acc register.
     *    acc  -> The values of all logic and arithmetic sentences;
     *    pc   -> Where I should look for an instruction;
     */
    byte stat = 0;     // Status
    byte acc  = 0;     // Acumulator
    byte pc   = 0;     // Program Counter

    byte memory[ MAX ];         // Simulate computer RAM

    bool status = true;

    /*
     *  Processor loop:
     *    1 -> Store operation
     *    2 -> Increase Program Counter
     *    3 -> Execute operation (switch-case)
     */
    while ( status )
    {
        byte opcode  = format[ pc ].opcode;
        byte operand = format[ pc ].operand;

        ++pc;
        
        switch ( opcode )
        {
            /*
             *     Code Format: load $adress
             *  Operation Code: 00
             *      Definition: Loads the value of memory[ adress ] in acc
             */
            case 0:
            {
                acc = memory[ operand ];
                
                setStat( &stat, ZEROACC, acc );

#ifdef ASM_FILE
                fprintf( assembly, "load  $ %-3d ; acc = %d\n", operand, memory[ operand ] );
#endif

                break;
            }

            /*
             *     Code Format: load 'number'
             *  Operation Code: 01
             *      Definition: Loads the value of 'number' in acc
             */
            case 1:
            {
                acc = operand;
                
                setStat( &stat, ZEROACC, operand );

#ifdef ASM_FILE
                fprintf( assembly, "load    %-3d ; acc = %d\n", operand, operand );
#endif

                break;
            }

            /*
             *     Code Format: store $adress
             *  Operation Code: 02
             *      Definition: Store the acc value in memory position defined by 'adress'
             */
            case 2:
            {
                memory[ operand ] = acc;

                setStat( &stat, ZEROACC, acc );
                
#ifdef ASM_FILE
                fprintf( assembly, "store $ %-3d ; mem[%d] = %d\n", operand, operand, acc );
#endif

                break;
            }

            /*
             *     Code Format: add $adress
             *  Operation Code: 03
             *      Definition: add the value in 'adress' position to acc
             */
            case 3:
            {
                setStat( &stat, CARRY, acc + memory[ operand ] );

                acc += memory[ operand ];
                
#ifdef ASM_FILE
                fprintf( assembly, "add   $ %-3d ; acc = %d\n", operand, acc );
#endif

                break;
            }

            /*
             *     Code Format: sub $adress
             *  Operation Code: 04
             *      Definition: subtract the value in 'adress' position to acc
             */
            case 4:
            {
                setStat( &stat, CARRY, acc - memory[ operand ] );
                
                acc -= memory[ operand ];

#ifdef ASM_FILE
                fprintf( assembly, "sub   $ %-3d ; acc = %d\n", operand, acc );
#endif

                break;
            }

            /*
             *     Code Format: mul $adress
             *  Operation Code: 05
             *      Definition: multiply acc with the value in 'adress'
             */
            case 5:
            {
                setStat( &stat, OVERFLOW, acc * memory[ operand ] );

                acc *= memory[ operand ];
               
#ifdef ASM_FILE
                fprintf( assembly, "mul   $ %-3d ; acc = %d\n", operand, acc );
#endif

                break;
            }

            /*
             *     Code Format: div $adress
             *  Operation Code: 06
             *      Definition: divide acc witn the value in 'adress'
             */
            case 6:
            {
                if ( memory[ operand ] != 0 )
                {
                    acc /= memory[ operand ];
                }
                
                setStat( &stat, OVERFLOW, memory[ operand ] != 0 ? acc : -1 );

#ifdef ASM_FILE
                fprintf( assembly, "div   $ %-3d ; acc = %d\n", operand, acc );
#endif

                break;
            }

            /*
             *     Code Format : inc
             *  Operation Code : 07
             *      Definition : increase in one unit acc
             */
            case 7:
            {
                setStat( &stat, CARRY, acc + 1 );

                ++acc;

#ifdef ASM_FILE
                fprintf( assembly, "inc         ; acc = %d\n", acc );
#endif

                break;
            }

            /*
             *     Code Format : dec
             *  Operation Code : 08
             *      Definition : decrease in one unit acc
             */
            case 8:
            {
                setStat( &stat, CARRY, acc-1 );

                --acc;

#ifdef ASM_FILE
                fprintf( assembly, "dec         ; acc = %d\n", acc );
#endif

                break;
            }

            /*
             *     Code Format : and $adress
             *  Operation Code : 09
             *      Definition : acc = acc & mem[ adress ]
             */
            case 9:
            {
                acc = acc & memory[ operand ];

                setStat( &stat, ZEROACC, acc );

#ifdef ASM_FILE
            fprintf( assembly, "and   $ %-3d ; acc = %d\n", operand, acc );
#endif

                break;
            }

            /*
             *     Code Format : or $adress
             *  Operation Code : 10
             *      Definition : acc = acc | mem[ adress ]
             */
            case 10:
            {
                acc = acc | memory[ operand ];

                setStat( &stat, ZEROACC, acc );
                
#ifdef ASM_FILE
                fprintf( assembly, "or    $ %-3d ; acc = %d\n", operand, acc );
#endif                

                break;
            }

            /*
             *     Code Format : not $adress
             *  Operation Code : 11
             *      Definition : mem[ adress ] = ~mem[ adress ]
             */
            case 11:
            {
                acc = ~acc;

                setStat( &stat, ZEROACC, acc );

#ifdef ASM_FILE
                fprintf( assembly, "not         ; acc = %d\n", acc );
#endif

                break;
            }

            /*
             *     Code Format : jmp #LABEL
             *  Operation Code : 12
             *      Definition : Go to 'LABEL'
             */
            case 12:
            {
                pc = operand / 2;

                break;
            }

            /*
             *     Code Format : jz #LABEL
             *  Operation Code : 13
             *      Definition : if acc equals to 0, go to 'LABEL'
             */
            case 13:
            {
                if ( stat & ZEROACC )
                {
                    pc = operand / 2;
                }

                break;
            }

            /*
             *     Code Format : jnz #LABEL
             *  Operation Code : 14
             *      Definition : if acc is not equal to 0, go to 'LABEL'
             */
            case 14:
            {
                if ( !( stat & ZEROACC ) )
                {
                    pc = operand / 2;
                }

                break;
            }

            /*
             *     Code Format : hlt
             *  Operation Code : 15
             *      Definition : end program (return 0)
             */
            case 15:
            {
                status = false;

#ifdef ASM_FILE
                fprintf( assembly, "hlt\n" );
                fclose( assembly );
#endif

                break;
            }

            default:
            {   
                fprintf( stderr, "Error: Unknown opcode %d. Value must be between 0 and 15.\n", opcode );
                
                status = false;

                break;
            }
        }
    }

    printf( "  acc: %03d\n" , acc );
    printf( " stat: xxxxx" );
    printf( "%c", stat & OVERFLOW ? '1' : '0' );
    printf( "%c", stat & CARRY    ? '1' : '0' );
    printf( "%c", stat & ZEROACC  ? '1' : '0' );
    printf( "\n" );
}

