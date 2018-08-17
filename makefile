OBJS = HashedObj.o HashTable.o 
CC = g++
DEBUG = -g
C11 = -std=c++11 
LFLAGS = -Wall $(DEBUG) $(C11) 
CFLAGS = $(LFLAGS) -c 
EXE = Lab5
SYSCMD = ./


all: $(OBJS) main.cpp 
	$(CC) $(LFLAGS) main.cpp $(OBJS) -o $(EXE) 

run: all 
	$(SYSCMD)$(EXE) 

HashedObj.o: HashedObj.h HashedObj.cpp 
	$(CC) $(CFLAGS) HashedObj.cpp

HashTable.o: HashedObj.o HashTable.h HashTable.cpp 
	$(CC) $(CFLAGS) HashTable.cpp 

clean: 
	rm -r *.o $(EXE) *.dSYM
