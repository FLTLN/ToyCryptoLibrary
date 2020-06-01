#!/bin/bash

if ! [ -d binaries ]; then
    mkdir binaries
fi

cp build/lib/libtcl.a build/perf/perfs build/test/tests binaries
