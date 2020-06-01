#!/bin/bash

if ! [ -d logs ]; then
    mkdir logs
fi

cd build/perf && ./perfs &> ../../logs/perf_tests.log

if [[ $? != 0 ]];
then
    exit $?
fi
