# !/bin/bash

# Compile Assembler
cd ./assembler/
make & make tab

# Run assembler to compile your assembly file
./sp1_assembler ../assemblies/simple.asm -o ./simple.bin
./sp1_assembler ../assemblies/loop.asm -o ./loop.bin
cd ../

# Compile and run SP1 Emulator
ccache gcc cpu.c stat.c -Wextra -Ofast -o ./sp1_processor

echo "simple.asm"
./sp1_processor ./assembler/simple.bin
echo "loop.asm"
./sp1_processor ./assembler/loop.bin
