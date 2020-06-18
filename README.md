# SP1-Emulator

This was coded as an university project to emulate a SP1 processor. It is a
hypothetical processor created to be simple and is intended to be the first step
towards more complex emulators.

## Testing it

To install all dependencies run:
```console
$ sudo bash dependencies.sh
```

After that, assuming all libraries was successfully installed, run:
```console
$ bash run.sh
```

## Notes

Additional assemblies can be compiled adding them to './src/test/' folder. The
changes you'll need to do is simply open 'run.sh' and add in 'Compile assembly
files' the new file you've added and the name of the file in 'Run SP1_Emulator'.
