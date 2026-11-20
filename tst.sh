#!/bin/bash

g++ brut.cpp -o br
g++ wzo.cpp -o wzo
g++ gen.cpp -o gen

for t in {1..100}; do
    gen > in
    br < in > out1
    wzo < in > out2
    diff -bew out1 out2 || break;
done