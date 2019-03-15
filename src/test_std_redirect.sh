#!/bin/bash

rm -f test.log
valgrind --error-exitcode=1 ./std_redirect --stdout=test.log -- date
if ! test -s test.log; then
    echo "failed"
    exit 1
fi
rm -f test.log
