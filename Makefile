CC = gcc
OFLAGS = -Wall -Werror -Wextra -Wconversion -pedantic -std=gnu11 -O0

all:	build_folders lab3 lab3original

lab3:	src/lab3.c
	$(CC) $(OFLAGS) -pg -o src/bin/lab3 src/lab3.c

lab3original:	src/lab3original.c
	$(CC) $(OFLAGS) -pg -o src/bin/lab3original src/lab3original.c

cppcheck: 
	cppcheck --enable=all --suppress=missingIncludeSystem src/*.c 2>err.txt

build_folders:
	mkdir -p ./src/bin

clean:
	rm -f -d src/bin/* src/bin gmon.out profiling/mio.txt profiling/original.txt profiling/analysis.txt err.txt runmio.txt runoriginal.txt