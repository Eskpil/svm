### SVM

Svm is just my toy virtual machine
which is now also hopefully turing complete

Right now the virtual machine is the center of the 
project, but in the future i suspect Sapphire will be
the main focus.

## Running

The run script is very simple, it expects two arguments, the operation and the project.
The operation argument can either be run or com. The difference is that run will compile 
and run the project whilst compile will just compile the project.
Currently the only project the run script can compile is `svm`.

To run the virtual machine use

```console
./run.sh run svm
``` 

### Sapphire

Sapphire is the official programming language for the virtual machine. 
Right now it is not implemented at all, but soon :).

(Take a look)[/sapphire]

### ASM

This directory is only temporary. It exists to make the writing of byte encoded arch instructions easier.
Too explore yourself, you must have nasm installed. 

How would i compile a file?

```console
nasm -felf64 ./[FILE].asm
```

If you want a actual executable pass the outputed object file to gnu linker like this.

```console
ld -o [FILE (could be anything really)] [FILE].o
```
