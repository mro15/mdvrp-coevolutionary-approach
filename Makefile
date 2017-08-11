CC = g++
CFLAGS = -Wall -O0

INCL = -I./include

DEPS =

OBJ = main.o

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCL)

clean:
	rm -f $(OBJ) core
