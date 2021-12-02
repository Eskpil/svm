#!/bin/sh

set -x

if [ -z $1 ]; then
    echo "You need to specify project, example ./run.sh svm" 
else 
    if [ -d "build" ]; then
        gcc -o build/$1 $1.c
        build/$1
    else 
        mkdir build
        gcc -o build/$1 $1.c
        build/$1
    fi
fi
