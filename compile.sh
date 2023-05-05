#!/usr/bin/env bash

set -x

rootDir=$(dirname $0)
mkdir -p $rootDir/build
cd $rootDir/build
cmake ..
make
