;	Assembly code

load    0   ; acc = 0
store $ 1   ; mem[1] = 0
load    1   ; acc = 1
store $ 3   ; mem[3] = 1
load    10  ; acc = 10
store $ 2   ; mem[2] = 10
load  $ 1   ; acc = 0
add   $ 2   ; acc = 10
store $ 1   ; mem[1] = 10
load  $ 2   ; acc = 10
sub   $ 3   ; acc = 9
store $ 2   ; mem[2] = 9
load  $ 1   ; acc = 10
add   $ 2   ; acc = 19
store $ 1   ; mem[1] = 19
load  $ 2   ; acc = 9
sub   $ 3   ; acc = 8
store $ 2   ; mem[2] = 8
load  $ 1   ; acc = 19
add   $ 2   ; acc = 27
store $ 1   ; mem[1] = 27
load  $ 2   ; acc = 8
sub   $ 3   ; acc = 7
store $ 2   ; mem[2] = 7
load  $ 1   ; acc = 27
add   $ 2   ; acc = 34
store $ 1   ; mem[1] = 34
load  $ 2   ; acc = 7
sub   $ 3   ; acc = 6
store $ 2   ; mem[2] = 6
load  $ 1   ; acc = 34
add   $ 2   ; acc = 40
store $ 1   ; mem[1] = 40
load  $ 2   ; acc = 6
sub   $ 3   ; acc = 5
store $ 2   ; mem[2] = 5
load  $ 1   ; acc = 40
add   $ 2   ; acc = 45
store $ 1   ; mem[1] = 45
load  $ 2   ; acc = 5
sub   $ 3   ; acc = 4
store $ 2   ; mem[2] = 4
load  $ 1   ; acc = 45
add   $ 2   ; acc = 49
store $ 1   ; mem[1] = 49
load  $ 2   ; acc = 4
sub   $ 3   ; acc = 3
store $ 2   ; mem[2] = 3
load  $ 1   ; acc = 49
add   $ 2   ; acc = 52
store $ 1   ; mem[1] = 52
load  $ 2   ; acc = 3
sub   $ 3   ; acc = 2
store $ 2   ; mem[2] = 2
load  $ 1   ; acc = 52
add   $ 2   ; acc = 54
store $ 1   ; mem[1] = 54
load  $ 2   ; acc = 2
sub   $ 3   ; acc = 1
store $ 2   ; mem[2] = 1
load  $ 1   ; acc = 54
add   $ 2   ; acc = 55
store $ 1   ; mem[1] = 55
load  $ 2   ; acc = 1
sub   $ 3   ; acc = 0
load  $ 1   ; acc = 55
hlt