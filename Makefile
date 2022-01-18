OBJECTS = wordpath.o graph.o file.o init.o printers.o
SHELL := /bin/bash

all : $(OBJECTS)
	gcc -O3 -o wordpath $(OBJECTS)

init.o : defs.h
wordpath.o : defs.h
graph.o : defs.h
file.o : defs.h
printers.o : defs.h

.PHONY : clean test
clean :
	rm -f wordpath graph $(OBJECTS)
test: wordpath
	./wordpath search real fake
	! ./wordpath search good evil
	./wordpath adjacent soup
	./wordpath farthest soup
	./wordpath isolated
