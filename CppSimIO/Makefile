CFLAGS = -Wall -g
CC = g++ -std=c++11


final: fileIO.o
	ar rvs fileIOlib fileIO.o


fileIO.o: fileIO.hpp fileIO.cpp
	$(CC) $(CFLAGS) -c fileIO.cpp

clean:
	rm -f *.o



