#!/bin/sh

set -ex

if [ -z $1 ]; then
    echo "You need to specify project, example ./run.sh svm" 
else 
    if [ -d "build" ]; then
        rm -f build/$1
        cd $1
        ./run.sh
        cd ..
        build/$1
    else 
        mkdir build
        cd $1
        ./run.sh
        cd ..
        build/$1
    fi
fi
