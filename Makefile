CC = g++
CFLAGS = -Wall -O0

INCL = -I./include

DEPS = graph.h

OBJ = main.o graph.o vertex.o

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCL)

clean:
	rm -f $(OBJ) main
