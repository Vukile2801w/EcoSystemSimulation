#!/usr/bin/env bash

set -e

cd build
make
./Windows/EcoSystem.exe
cd ..