#!/bin/sh

set -ex

if [ -z $1 ]; then
    echo "You need to specify project, example ./run.sh svm" 
else 
    if [ -d "build" ]; then
        gcc -Wall -Wextra -Wswitch-enum -Wmissing-prototypes -Wconversion -Wno-missing-braces -pedantic -Wformat=1 -o build/$1 -std=c11 $1/*.c
        build/$1
    else 
        mkdir build
        gcc -o build/$1 -std=c11 $1/*.c
        build/$1
    fi
fi
