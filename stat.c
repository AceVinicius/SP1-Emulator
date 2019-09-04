# include "./headers/include.h"
# include "./headers/define.h"
# include "./headers/stat.h"



void
setStat(byte    *stat,
        byte     test,
        int32_t  var )
{
    *stat = 0;
    
    *stat += zeroACC(var);

    if(test == OVERFLOW)
    {
        *stat += overflow(var);
    }
    else if(test == CARRY)
    {
        *stat += carry(var);
    }


    DEBUG( printf("DEBUG:  O:%2c  C:%2c  Z:%2c\n", *stat & OVERFLOW ? '1' : '0', *stat & CARRY ? '1' : '0', *stat & ZEROACC ? '1' : '0'); )

    return;
}



byte
zeroACC(int32_t var)
{   
    if(var == 0)
    {
        return ZEROACC;
    }

    return OK;
}



byte
carry(int32_t var)
{   
    if(var > 255 || var < 0)
    {
        return CARRY;
    }

    return OK;
}



byte
overflow(int32_t var)
{   
    if(var == 0)
    {
        return OVERFLOW;
    }

    return OK;
}
