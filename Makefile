binname 			:= halk
exec 				:= $(binname).out

compiler 		:= clang
flags 			:= -g

sources 			:= $(wildcard src/*.c)
sources 			:= $(filter-out src/parser.c, $(sources)) # exclude the incomplete parser for now.
objects 			:= $(sources:.c=.o)


$(exec): $(objects)
	$(compiler) $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	$(compiler) -c $(flags) $< -o $@

install:
	make
	cp ./$(exec) /usr/local/bin/$(binname)

uninstall:
	rm -f /usr/local/bin/$(binname) 

clean:
	rm -f *.out *.o src/*.o
