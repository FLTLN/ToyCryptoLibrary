#!/bin/bash

if ! [ -d logs ]; then
    mkdir logs
fi

cd build/test && ./tests &> ../../logs/alg_tests.log

if [[ $? != 0 ]];
then
    exit $?
fi
