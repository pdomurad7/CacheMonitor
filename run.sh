#!/usr/bin/env bash

rootDir=$(dirname $0)

if [[ "$@" == *"--build"* ]] || [[ "$@" == *"-b"* ]]; then
    $rootDir/compile.sh
    ./build/cache_monitor
else
    ./build/cache_monitor
fi
