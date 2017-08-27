CC = g++
CFLAGS = -Wall -O0

INCL = -I./include

DEPS = ./include/graph.h ./include/vertex.h ./include/solver.h \
		./include/operation.h ./include/population.h ./include/individual.h \
		./include/operators.h

OBJ = main.o graph.o vertex.o solver.o operation.o \
		population.o individual.o operators.o

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: src/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCL)

clean:
	rm -f $(OBJ) main
