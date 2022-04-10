CC = gcc
OFLAGS = -Wall -Werror -Wextra -Wconversion -pedantic -std=gnu11 -O0

all:	lab3

lab3:	lab3.c
	$(CC) $(OFLAGS) -pg -o lab3 lab3.c

lab3original:	lab3original.c
	$(CC) $(OFLAGS) -pg -o lab3original lab3original.c

gmon: 
	./lab3
	gprof lab3 gmon.out > analysis.txt

cppcheck: 
	cppcheck --enable=all --suppress=missingIncludeSystem lab3.c 2>err.txt
                
clean:
	rm -f lab3 lab3original gmon.out 