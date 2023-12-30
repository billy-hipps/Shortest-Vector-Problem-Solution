OUTPUTS = runme test
OBJECTS = common.o getBasis.o getVecs.o listSieve.o reduce.o sample.o writeTXT.o
DEPS = common.h getBasis.h getVecs.h listSieve.h reduce.h sample.h writeTXT.h
CC = gcc


all: $(OBJECTS) main.c $(DEPS)
	$(CC) -o runme main.c $(OBJECTS) -lm

%.o: %.c $(DEPS)
	$(CC) -c $< -o $@

%.o: tests/%.c $(OBJECTS)
	$(CC) -c $< -o $@ 

clean: 
	rm -rf $(OUTPUTS) $(OBJECTS)

test: $(OBJECTS) 
	$(CC) -o test $(OBJECTS)
	./test 