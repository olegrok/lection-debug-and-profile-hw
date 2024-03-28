#!/usr/bin/env bash

./build/tests
lcov -t "tests" -o tests.info -c -d .
genhtml -o report tests.info
