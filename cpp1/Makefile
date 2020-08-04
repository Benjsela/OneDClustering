CFLAGS = -Wall -g
CC = g++ -std=c++11 -I ../DistLibrary
LIB = ../DistLibrary/distslib

code: definitions.o cluster1.o main.o utils.o
	$(CC) $(CFLAGS) -o code definitions.o cluster1.o main.o utils.o $(LIB)




definitions.o: definitions.cpp definitions.hpp
	$(CC) $(CFLAGS) -c definitions.cpp


utils.o: utils.cpp utils.hpp
	$(CC) $(CFLAGS) -c utils.cpp

cluster1.o: cluster1.cpp cluster1.hpp
	$(CC) $(CFLAGS) -c cluster1.cpp


clean:
	rm -f *.o
