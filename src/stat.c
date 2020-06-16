#include <stdint.h>

#include "./../lib/include/define.h"
#include "./../lib/include/stat.h"

#ifdef DEBUG
# include <stdio.h>
#endif




void
setStat(       byte    *stat ,
         const byte     test ,
         const int32_t  var  )
{
    *stat = zeroACC(var);

    if ( test == OVERFLOW )
    {
        *stat += overflow( var );
    }
    else if ( test == CARRY )
    {
        *stat += carry( var );
    }

#ifdef DEBUG
    printf( "DEBUG:  stat: " );
    printf( "%c", *stat & OVERFLOW ? '1' : '0' );
    printf( "%c", *stat & CARRY    ? '1' : '0' );
    printf( "%c", *stat & ZEROACC  ? '1' : '0' );
    printf( "\n" );
#endif
}



byte
zeroACC( const int32_t var )
{   
    return ( var == 0 ? ZEROACC : OK );
}



byte
carry( const int32_t var )
{   
    if( var < 0 || var > 255 )
    {
        return CARRY;
    }

    return OK;
}



byte
overflow( const int32_t var )
{   
    if ( var < 0 || var > 255 )
    {
        return OVERFLOW;
    }

    return OK;
}
