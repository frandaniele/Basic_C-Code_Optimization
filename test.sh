#!/bin/bash
./lab3 > runmio.txt
gprof lab3 gmon.out > profiling/mio.txt
./lab3original > runoriginal.txt
gprof lab3original gmon.out > profiling/original.txt
diff --suppress-common-lines -y runoriginal.txt runmio.txt 