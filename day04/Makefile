HEADERS = main.h ../util/util.h
OBJECTS = main.o ../util/util.o

default: run

%.o: %.c $(HEADERS)
	gcc -c $< -o $@

run: $(OBJECTS)
	gcc $(OBJECTS) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f main