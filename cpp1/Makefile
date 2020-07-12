CFLAGS = -Wall -g
CC = g++ -std=c++11


code: definitions.o cluster1.o main.o
	$(CC) $(CFLAGS) -o code definitions.o cluster1.o main.o




definitions.o: definitions.cpp definitions.hpp
	$(CC) $(CFLAGS) -c definitions.cpp




cluster1.o: cluster1.cpp cluster1.hpp
	$(CC) $(CFLAGS) -c cluster1.cpp


clean:
	rm -f *.o
