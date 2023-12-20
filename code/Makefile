OUTPUTS = runme 
OBJECTS = common.o
DEPS = common.h
CC = gcc


all: $(OBJECTS) main.c $(DEPS)
	$(CC) -o $(OUTPUTS) main.c $(OBJECTS) 

%.o: %.c $(DEPS)
	$(CC) -c $< -o $@

%.o: tests/%.c $(OBJECTS)
	$(CC) -c $< -o $@ 

clean: 
	rm -rf $(OUTPUTS) $(OBJECTS)

test: $(OBJECTS) 
	$(CC) -o test $(OBJECTS)
	./test 