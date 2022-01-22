#!/bin/sh

set -e

CFLAGS="-Wall -Wextra -Wpedantic -std=gnu11"

compile() {
    echo "[Info] Compiling $1"
    if [  -d "build/$1" ]; then
        echo "[Info] There is no previous version of $1"
    else
        echo "[Info] A previous compiled version of $1 already exists, removing it"
        rm -f build/$1
    fi

    echo "                                                              "
    echo "--------------------------------------------------------------"
    echo "                                                              "

    $CC -I common/ -g common/*.c $CFLAGS -o build/$1 $1/*.c $1/*.h
}

if [ -z $1  ] || [ -z $2 ]; then
    echo "[Error] You must specify operation, example ./run.sh run svm"
    echo "[Error] You need to specify project, example ./run.sh run svm" 
else 
    if [ -d "build" ]; then
        echo "[Info] Build directory exits, so skipping to compilation part"
    else
        echo "[Info] Build Birectory does not exist, creating it"
        mkdir build

    fi 

    if [ "$1" = "run" ]; then 
        compile $2
        echo "[Info] Compilation finished, running the $(echo $2) executable"
        echo "                                                              "
        echo "--------------------------------------------------------------"
        echo "                                                              "

        build/$2
    else
        compile $2
        echo "[Info] Compilation finished, exectuable is located here: build/$2" 
    fi
fi
