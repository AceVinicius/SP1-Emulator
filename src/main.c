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
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "./../lib/include/constants.h"
#include "./../lib/include/define.h"
#include "./../lib/include/cpu.h"

#ifdef ASM_FILE
# include <string.h>
#endif



int
main(       int   argc   ,
      const char *argv[] )
{
    for ( int binary = 1; binary < argc; ++binary )
    {
        INSTRUCTION format[ MAX ];  // Store instruction for post execution

        byte buffer[ QTD_ARG ];     // Separe file input in two parts


        FILE *binary_file = fopen( argv[ binary ], "rb" );
        if ( binary_file == NULL )
        {
            fprintf( stderr, binary_file_open_error, argv[ binary ] );
            continue;
        }

        for ( int i = 0; fread( buffer, sizeof( byte ), QTD_ARG, binary_file ); ++i )
        {
            format[ i ].opcode  = *( buffer );
            format[ i ].operand = *( buffer+1 );

#ifdef DEBUG
            printf( "DEBUG:  opcode:%-3u  operand:%-3u\n", format[ i ].opcode, format[ i ].operand );
#endif
        }

        fclose( binary_file );

#ifdef ASM_FILE
        char ASM_PATH[ 100 ] = "./../lib/debug/ASM_FILE_";

        strcat( ASM_PATH, argv[ binary ] );
        strcat( ASM_PATH, ".asm" );

        FILE *assembly = fopen( ASM_PATH, "w" );
        if ( assembly == NULL )
        {
            fprintf( stderr, asm_file_debug_error, ASM_PATH );
            continue;
        }
        fprintf( assembly, ";\tAssembly code\n\n" );
#endif

        printf( "\n\t%s\n\n", argv[ binary ] );

        cpu( format
#ifdef ASM_FILE
           , assembly
#endif
        );
    }

    return EXIT_SUCCESS;
}
