#ifndef STAT_H
# define STAT_H



void  setStat   (byte    *stat,
                 byte     test,
                 int32_t  var );

byte  zeroACC   (int32_t var);

byte  carry     (int32_t var);

byte  overflow  (int32_t var);



#endif  // STAT_H
