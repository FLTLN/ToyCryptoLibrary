#!/bin/bash

if [ -d build ]; then
    rm -rd build
fi

if [ -d logs ]; then
    rm -rd logs
fi

if [ -d binaries ]; then
    rm -rd binaries
fi
