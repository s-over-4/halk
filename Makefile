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
	cp ./$(name) $(HOME)/.local/bin/$(name)

uninstall:
	rm -f $(HOME)/.local/bin/$(name)

clean:
	rm -f ./$(name) ./src/*.o

me:
	@[ "$(USER)" = "root" ] && echo "Okay." || echo "What? Make it yourself."

a sandwich:
	@exit

.PHONY: install uninstall clean me a sandwich
