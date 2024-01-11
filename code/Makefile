OUTPUTS = runme test
OBJECTS = checkArgs.o common.o cosScore.o getBasis.o listSieve.o reduce.o sample.o
DEPS = checkArgs.h common.h cosScore.h getBasis.h listSieve.h reduce.h sample.h
CC = gcc
CFLAGS = -Wall -Wextra

all: $(OBJECTS) main.c $(DEPS)
	$(CC) $(CFLAGS) -g -o runme main.c $(OBJECTS) -lm

%.o: %.c $(DEPS)
	$(CC) -g -c $< -o $@

%.o: tests/%.c $(OBJECTS)
	$(CC) -c $< -o $@

clean:
	rm -rf $(OUTPUTS) $(OBJECTS)

test: $(OBJECTS)
	$(CC) -o test $(OBJECTS)
	./test