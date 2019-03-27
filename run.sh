# !/bin/bash

# Compile Assembler
cd ./assembler/
make
make tab


# Run assembler to compile your assembly file
./sp1a ../assemblies/loop.asm -o ./test.bin
cd ../


# Compile and run SP1 Emulator
ccache gcc cpu.c -Wall -o ./sp1_processor
./sp1_processor ./assembler/test.bin
