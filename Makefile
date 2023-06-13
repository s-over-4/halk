name 				:= halk
cc 				:= cc
flags 			:= -g
sources 			:= $(wildcard src/*.c)
sources 			:= $(filter-out src/parser.c, $(sources)) # exclude the incomplete parser for now.
objects 			:= $(sources:.c=.o)

$(name): $(objects)
	$(cc) $(objects) $(flags) -o ./$(name)

%.o: %.c include/%.h
	$(cc) -c $(flags) $< -o $@

install:
	make
	[ $(XDG_DATA_HOME) ] && cp ./$(name) $(XDG_DATA_HOME)/bin/$(name) || cp ./$(name) /usr/local/bin/$(name)

uninstall:
	[ $(XDG_DATA_HOME) ] && rm -f $(XDG_DATA_HOME)/bin/$(name) || rm -f /usr/local/bin/$(name)

clean:
	rm -f ./$(name) ./src/*.o

me:
	@[ "$(USER)" = "root" ] && echo "Okay." || echo "What? Make it yourself."

a sandwich:
	@exit

.PHONY: install uninstall clean me a sandwich
