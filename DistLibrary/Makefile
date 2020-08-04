CFLAGS = -Wall -g
CC = g++ -std=c++11


final: customDistributions.o
	ar rvs distslib customDistributions.o

customDistributions.o: customDistributions.hpp customDistributions.cpp
	$(CC) $(CFLAGS) -c customDistributions.cpp




clean:
	rm -f *.o


