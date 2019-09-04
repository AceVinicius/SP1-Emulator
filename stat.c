# include "./headers/include.h"
# include "./headers/define.h"
# include "./headers/stat.h"



void
setStat(uint8_t *stat,
        uint8_t  test,
        int32_t  var )
{
    *stat = zeroACC(var);

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



uint8_t
zeroACC(int32_t var)
{   
    if(var == 0)
    {
        return ZEROACC;
    }

    return OK;
}



uint8_t
carry(int32_t var)
{   
    if(var < 0 || var > 255)
    {
        return CARRY;
    }

    return OK;
}



uint8_t
overflow(int32_t var)
{   
    if(var < 0 || var > 255)
    {
        return OVERFLOW;
    }

    return OK;
}
