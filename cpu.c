/********************************************************************************
 ********************************************************************************
 *****                                                                      *****
 *****                       Engenharia de Computação                       *****
 *****                                                                      *****
 *****                              SP1 Emulator                            *****
 *****                             Version 0.0.1                            *****
 *****                                                                      *****
 *****                            Vinícius Aguiar                           *****
 *****                                                                      *****
 *****                        26.02.2019 - 28.03.2019                       *****
 *****                                                                      *****
 ********************************************************************************
 ********************************************************************************/



# include "./headers/include.h"
# include "./headers/define.h"
# include "./headers/stat.h"



typedef struct format
{
    byte operand;     // Identifier  -> 0b00000000 (0) to 0b11111111 (255)
    byte opcode;      // Instruction -> 0b00000000 (0) to 0b00001111  (15)
} INSTRUCTION;



int
main(      int   argc  ,
     const char *argv[])
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
    byte buffer[ QTD_ARG ];     // Separe file input in two parts

    INSTRUCTION format[ MAX ];     // Store instruction for post execution


    FILE *program = fopen(argv[ 1 ], "rb");
    if (program == NULL)
    {
        fprintf(stderr, "Error: Need to provide the file's name.\n");
        return EXIT_FAILURE;
    }

    while (fread(buffer, sizeof(byte), 1 << 1, program))
    {
        format[ pc ].opcode  = *(buffer);
        format[ pc ].operand = *(buffer+1);

        ++pc;

        
        /*
         *  Print debug (on/off in "define.h")
         */
        DEBUG( printf("DEBUG:  opcode:%-3u  operand:%-3u\n", format[ pc-1 ].opcode, format[ pc-1 ].operand); )
    }
    fclose(program);


    /*
     *  print assembly (on/off in "define.h")
     */
    ASM_FILE( FILE *assembly = fopen("./assemblies/ASM_FILE.asm", "w");      )
    ASM_FILE( if (!assembly)                                                 )
    ASM_FILE( {                                                              )
    ASM_FILE(     fprintf(stderr, "Error: Cannot generate assembly file\n"); )
    ASM_FILE( }                                                              )
    ASM_FILE( fprintf(assembly, ";\tAssembly code\n\n");                   )


    bool status = true;
    
    pc = 0;
    /*
     *  Processor loop:
     *    1 -> Store operation
     *    2 -> Increase Program Counter
     *    3 -> Execute operation (switch-case)
     */
    while (status)
    {
        byte opcode  = format[ pc ].opcode;
        byte operand = format[ pc ].operand;

        ++pc;
        
        switch (opcode)
        {
            /*
             *     Code Format: load $adress
             *  Operation Code: 00
             *      Definition: Loads the value of memory[ adress ] in acc
             */
            case 0:
            {
                acc = memory[ operand ];
                
                setStat(&stat, ZEROACC, acc);


                ASM_FILE( fprintf(assembly, "load  $ %-3d ; acc = %d\n", operand, memory[ operand ]); )

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
                
                setStat(&stat, ZEROACC, operand);


                ASM_FILE( fprintf(assembly, "load    %-3d ; acc = %d\n", operand, operand); )

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

                setStat(&stat, ZEROACC, acc);
                
                
                ASM_FILE( fprintf(assembly, "store $ %-3d ; mem[%d] = %d\n", operand, operand, acc); )

                break;
            }

            /*
             *     Code Format: add $adress
             *  Operation Code: 03
             *      Definition: add the value in 'adress' position to acc
             */
            case 3:
            {
                setStat(&stat, CARRY, acc + memory[ operand ]);

                acc += memory[ operand ];
                
                
                ASM_FILE( fprintf(assembly, "add   $ %-3d ; acc = %d\n", operand, acc); )

                break;
            }

            /*
             *     Code Format: sub $adress
             *  Operation Code: 04
             *      Definition: subtract the value in 'adress' position to acc
             */
            case 4:
            {
                setStat(&stat, CARRY, acc - memory[ operand ]);
                
                acc -= memory[ operand ];


                ASM_FILE( fprintf(assembly, "sub   $ %-3d ; acc = %d\n", operand, acc); )

                break;
            }

            /*
             *     Code Format: mul $adress
             *  Operation Code: 05
             *      Definition: multiply acc with the value in 'adress'
             */
            case 5:
            {
                setStat(&stat, OVERFLOW, acc * memory[ operand ]);

                acc *= memory[ operand ];
               
               
                ASM_FILE( fprintf(assembly, "mul   $ %-3d ; acc = %d\n", operand, acc); )

                break;
            }

            /*
             *     Code Format: div $adress
             *  Operation Code: 06
             *      Definition: divide acc witn the value in 'adress'
             */
            case 6:
            {
                if (memory[ operand ] != 0)
                {
                    acc /= memory[ operand ];    
                }
                
                setStat(&stat, OVERFLOW, memory[ operand ] != 0 ? acc : -1);
                

                ASM_FILE( fprintf(assembly, "div   $ %-3d ; acc = %d\n", operand, acc); )

                break;
            }

            /*
             *     Code Format : inc
             *  Operation Code : 07
             *      Definition : increase in one unit acc
             */
            case 7:
            {
                setStat(&stat, CARRY, acc + 1);

                ++acc;
                                

                ASM_FILE( fprintf(assembly, "inc         ; acc = %d\n", acc); )

                break;
            }

            /*
             *     Code Format : dec
             *  Operation Code : 08
             *      Definition : decrease in one unit acc
             */
            case 8:
            {
                setStat(&stat, CARRY, acc - 1);

                --acc;


                ASM_FILE( fprintf(assembly, "dec         ; acc = %d\n", acc); )

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
                
                setStat(&stat, ZEROACC, acc);
                
                
                ASM_FILE( fprintf(assembly, "and   $ %-3d ; acc = %d\n", operand, acc); )

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

                setStat(&stat, ZEROACC, acc);
                
                
                ASM_FILE( fprintf(assembly, "or    $ %-3d ; acc = %d\n", operand, acc); )

                break;
            }

            /*
             *     Code Format : not $adress
             *  Operation Code : 11
             *      Definition : mem[ adress ] = ~mem[ adress ]
             */
            case 11:
            {
                memory[ operand ] = ~memory[ operand ];

                setStat(&stat, ZEROACC, acc);


                ASM_FILE( fprintf(assembly, "not   $ %-3d ; mem[%d] = %d\n", operand, operand , memory[ operand ]); )

                break;
            }

            /*
             *     Code Format : jmp #LABEL
             *  Operation Code : 12
             *      Definition : Go to 'LABEL'
             */
            case 12:
            {
                pc = operand;

                setStat(&stat, ZEROACC, acc);

                break;
            }

            /*
             *     Code Format : jz #LABEL
             *  Operation Code : 13
             *      Definition : if acc equals to 0, go to 'LABEL'
             */
            case 13:
            {
                if (stat & ZEROACC)
                {
                    pc = operand / 2;
                }

                setStat(&stat, ZEROACC, acc);

                break;
            }

            /*
             *     Code Format : jnz #LABEL
             *  Operation Code : 14
             *      Definition : if acc is not equal to 0, go to 'LABEL'
             */
            case 14:
            {
                if (!(stat & ZEROACC))
                {
                    pc = operand / 2;
                }

                setStat(&stat, ZEROACC, acc);

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


                ASM_FILE( fprintf(assembly, "hlt\n"); )
                ASM_FILE( fclose(assembly);           )
                
                break;
            }

            default:
            {   
                fprintf(stderr, "Error: Unknown opcode %d. Value must be between 0 and 15.\n", opcode);

                return EXIT_FAILURE;

                break;
            }
        }
    }

    printf("  acc: %03d\n" , acc);
    printf(" stat: xxxxx%c", stat & OVERFLOW ? '1' : '0');
    printf("%c"            , stat & CARRY    ? '1' : '0');
    printf("%c\n"          , stat & ZEROACC  ? '1' : '0');

    return EXIT_SUCCESS;
}
