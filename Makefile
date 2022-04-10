CC = gcc
OFLAGS = -Wall -Werror -Wextra -Wconversion -pedantic -std=gnu11 -O0

lab3:	lab3.c
	$(CC) $(OFLAGS) -pg -o lab3 lab3.c

gmon: 
	./lab3
	gprof lab3 gmon.out > analysis.txt

cppcheck: 
	cppcheck --enable=all --suppress=missingIncludeSystem lab3.c 2>err.txt
                
clean:
	rm -f lab3 gmon.out 