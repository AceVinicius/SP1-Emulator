load     5
store   $1
load     2
add     $1
div     $1
store   $3
load   254
store   $2
not     $2
load    $2
inc
add     $1
mul     $3
#WHILE:
    dec
    store   $4
    jnz #WHILE
add     $1
add     $3
add     $4
hlt
