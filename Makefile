all: runMovies

main.o: movies.cpp movies.h main.cpp
	g++ --std=c++11 -Wall -g movies.cpp main.cpp -c

runMovies: main.o movies.o
	g++ --std=c++11 -Wall -g main.o movies.o -o runMovies

clean: 
	rm runMovies*.o
