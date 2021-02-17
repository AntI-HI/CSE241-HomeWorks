objects = Functions.o

CC_CPP = $(CROSS_TOOL)g++

CFLAGS = -std=c++11 -g -Wall

out : $(objects) main.o
	$(CC_CPP) -o out main.o $(objects) && ./out

main.o : main.cpp
	$(CC_CPP) -c $(CFLAGS) main.cpp

Functions.o : Functions.cpp Functions.h
	$(CC_CPP) -c $(CFLAGS) Functions.cpp

clean:
	rm *.o out
