objects =  FinalMove.o AbstractHex.o Cell.o AI_POS_List.o HexVector.o HexAdapter.o HexArray1D.o

CC_CPP = $(CROSS_TOOL)g++

CFLAGS = -std=c++11 -Wall -g

out : $(objects) main.o
	$(CC_CPP) -o out main.o $(objects) && ./out

main.o : main.cpp
	$(CC_CPP) -c $(CFLAGS) main.cpp

FinalMove.o : FinalMove.cpp FinalMove.h
	$(CC_CPP) -c $(CFLAGS) FinalMove.cpp

AbstractHex.o : AbstractHex.h AbstractHex.cpp
	$(CC_CPP) -c $(CFLAGS) AbstractHex.cpp

Cell.o : Cell.h Cell.cpp
	$(CC_CPP) -c $(CFLAGS) Cell.cpp

AI_POS_List.o : AI_POS_List.h AI_POS_List.cpp
	$(CC_CPP) -c $(CFLAGS) AI_POS_List.cpp

HexVector.o : HexVector.h HexVector.cpp
	$(CC_CPP) -c $(CFLAGS) HexVector.cpp

HexAdapter.o : HexAdapter.cpp
	$(CC_CPP) -c $(CFLAGS) HexAdapter.cpp

HexArray1D.o : HexArray1D.h HexArray1D.cpp
	$(CC_CPP) -c $(CFLAGS) HexArray1D.cpp

clean:
	rm *.o out
