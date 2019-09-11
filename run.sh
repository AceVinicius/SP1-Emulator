# !/bin/bash

# Compile Assembler
cd lib/assembler
# make & make tab

# Compile assembly files
cd ../../bin
./sp1_assembler ../src/test/simple.asm -o sp1_simple
./sp1_assembler ../src/test/loop.asm   -o sp1_loop

# Create Obj files
cd ../src
ccache gcc cpu.c  -c -Wall -W -O3 -o ../obj/cpu.o
ccache gcc stat.c -c -Wall -W -O3 -o ../obj/stat.o

# Create static library
cd ../obj
ar -rcs libsp1.a cpu.o stat.o

# Compile and link sp1_library
cd ../src
ccache gcc main.c -lsp1 -L../obj -Wall -W -O3 -o ../bin/sp1_emulator

# Run SP1_Emulator
cd ../bin
./sp1_emulator sp1_simple sp1_loop
