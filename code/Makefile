OUTPUTS = runme test
OBJECTS = checkArgs.o common.o getBasis.o listSieve.o reduce.o sample.o writeTXT.o
DEPS = checkArgs.h common.h getBasis.h listSieve.h reduce.h sample.h writeTXT.h
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