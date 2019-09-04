#ifndef STAT_H
# define STAT_H



void     setStat   (uint8_t *stat,
                    uint8_t  test,
                    int32_t  var );

uint8_t  zeroACC   (int32_t var);

uint8_t  carry     (int32_t var);

uint8_t  overflow  (int32_t var);



#endif  // STAT_H