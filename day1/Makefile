HEADERS = day1.h ../util/util.h
OBJECTS = day1.o ../util/util.o

default: day1

%.o: %.c $(HEADERS)
	gcc -c $< -o $@

day1: $(OBJECTS)
	gcc $(OBJECTS) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f day1