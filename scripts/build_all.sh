#!/bin/bash

if ! [ -d logs ]; then
    mkdir logs
fi

if ! [ -d build ]; then
    cmake CMakeLists.txt -B"build" &> logs/cmake.log

    if [[ $? != 0 ]];
    then 
        exit $?
    fi
fi

cd build 

make -j8 &> ../logs/make.log

if [[ $? = 0 ]];
then 
    exit $?
fi
