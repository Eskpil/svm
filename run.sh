#!/bin/sh

set -ex

if [ -z $1 ]; then
    echo "You need to specify project, example ./run.sh svm" 
else 
    if [ -d "build" ]; then
        rm -f build/$1
        gcc -I common/ -g common/*.c -Wall -pedantic -std=gnu11 -o build/$1 $1/*
        build/$1
    else 
        mkdir build
        gcc -I common/ -g common/*.c -Wall -pedantic -std=gnu11 -o build/$1 $1/*
        build/$1
    fi
fi
