OBJECTS = wordpath.o graph.o file.o init.o
SHELL := /bin/bash

all : $(OBJECTS)
	gcc -O3 -o wordpath $(OBJECTS)

init.o : defs.h
wordpath.o : defs.h
graph.o : defs.h
file.o : defs.h

.PHONY : clean
clean :
	rm -f wordpath graph $(OBJECTS)
