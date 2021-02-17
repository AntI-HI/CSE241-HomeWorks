objects = hex.o

CC_CPP = $(CROSS_TOOL)g++

CFLAGS = -std=c++11 -Wall -g

out : $(objects) main.o
	$(CC_CPP) -o out main.o $(objects) && ./out

main.o : main.cpp
	$(CC_CPP) -c $(CFLAGS) main.cpp

hex.o : hex.cpp hex.h
	$(CC_CPP) -c $(CFLAGS) hex.cpp

clean:
	rm *.o out
