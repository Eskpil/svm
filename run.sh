#!/bin/sh

set -x

gcc -o build/$1 $1.c
build/$1
