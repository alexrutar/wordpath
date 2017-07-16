OBJECTS = parse.o graph.o file.o init.o
all : $(OBJECTS)
	gcc -o wordpath $(OBJECTS)

graph.o : defs.h
file.o : defs.h
parse.o : defs.h
init.o : defs.h
	
.PHONY : clean
clean :
	rm wordpath graph $(OBJECTS)
