#!/bin/bash

cargo b --release
mv target/release/sasm ../build/sasm
