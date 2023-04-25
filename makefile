prog:	main.o
			g++ main.o -o PA5

main.o: main.cpp Hash.h ChainingHash.h ProbingHash.h ParallelProbingHash.h
			g++ -c -g -Wall -std=c++11 main.cpp

clean:
			-rm *.o

run:
			@./PA5