CC=g++
CFLAGS = -O2 -Wall

day5: main.o SolutionFirst.o SolutionSecond.o
	${CC} ${CFLAGS} main.o SolutionFirst.o SolutionSecond.o

main.o: main.cpp SolutionFirst.h SolutionSecond.h
	${CC} ${CFLAGS} -c main.cpp
SolutionFirst.o: SolutionFirst.cpp SolutionFirst.h
	${CC} ${CFLAGS} -c SolutionFirst.cpp
SolutionSecond.o: SolutionSecond.cpp SolutionSecond.h
	${CC} ${CFLAGS} -c SolutionSecond.cpp
clean:
	del main.o SolutionFirst.o SolutionSecond.o day5.exe a.exe