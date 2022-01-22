#!/bin/sh

set -ex

$CC -ggdb3 -ffreestanding -masm=intel -nostdlib -o build/runtime src/*
