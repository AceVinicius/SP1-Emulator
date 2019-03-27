# !/bin/bash

# Install dependencies
sudo apt install make
sudo apt install gcc
sudo apt install ccache
sudo apt install bison
sudo apt install flex


# Compile Assembler
cd ./assembler/
make
make tab


# Run assembler to compile your assembly file
./sp1a ../assemblies/loop.asm -o ./test.bin
cd ../


# Compile and run SP1 Emulator
bash run.sh
