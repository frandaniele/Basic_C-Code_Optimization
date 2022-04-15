#!/bin/bash
start=`date +%s.%N`

./src/bin/lab3 > runmio.txt

end=`date +%s.%N`
sleep 1
runtime=$( echo "$end - $start" | bc -l )
echo 'El tiempo de ejecucion optimizado es' $runtime 'segundos'

gprof src/bin/lab3 gmon.out > profiling/mio.txt

sleep 1

start=`date +%s.%N`

./src/bin/lab3original > runoriginal.txt

end=`date +%s.%N`
sleep 1
runtime=$( echo "$end - $start" | bc -l )
echo 'El tiempo de ejecucion sin optimizar es' $runtime 'segundos'

sleep 1

gprof src/bin/lab3original gmon.out > profiling/original.txt

diff --suppress-common-lines -y runoriginal.txt runmio.txt | tail