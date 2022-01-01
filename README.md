### SVM

Svm is just my toy virtual machine
which is now also hopefully turing complete

Windows or macos is of no priority
but i am open to pr for windows or macos

## Running

The run script is very simple, it expects two arguments, the operation and the project.
The operation argument can either be run or com. The difference is that run will compile 
and run the project whilst compile will just compile the project.
Currently the only project the run script can compile is `svm`.

To run the virtual machine use

```console
./run.sh run svm
``` 

### ASM

This directory is only temporary. It exists to make the writing of byte encoded arch instructions easier.
