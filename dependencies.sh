# !/bin/bash

# Install dependencies
sudo dnf install make
sudo dnf install gcc
sudo dnf install ccache
sudo dnf install bison
sudo dnf install flex

# Compile and run SP1 Emulator
bash run.sh
