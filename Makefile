exec = halk.out
sources := $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g

$(exec): $(objects)
	clang $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	clang -c $(flags) $< -o $@

install:
	make
	cp ./halk.out /usr/local/bin/halk

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o
