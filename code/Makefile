OUTPUTS = runme test
OBJECTS = common.o getVecs.o listSieve.o reduce.o sample.o 
DEPS = common.h getVecs.h listSieve.h reduce.h sample.h getVecs.h
CC = gcc


all: $(OBJECTS) main.c $(DEPS)
	$(CC) -o runme main.c $(OBJECTS) 

%.o: %.c $(DEPS)
	$(CC) -c $< -o $@

%.o: tests/%.c $(OBJECTS)
	$(CC) -c $< -o $@ 

clean: 
	rm -rf $(OUTPUTS) $(OBJECTS)

test: $(OBJECTS) 
	$(CC) -o test $(OBJECTS)
	./test 