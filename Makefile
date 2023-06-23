PREFIX			:= /usr/local
BINDIR			:= $(PREFIX)/bin
BIN 				:= halk
TMPBIN			:= halk.out
CC					:= gcc
FLAGS				:=
DEVFLAGS			:= -ggdb -fsanitize=leak,address,undefined -fno-omit-frame-pointer
SRCS 				:= $(wildcard src/*.c)
SRCS 				:= $(filter-out src/parser.c, $(SRCS)) # exclude the incomplete parser for now.
OBJS 				:= $(SRCS:.c=.o)

all: options HALK

options:
	@echo "HALK build options		"
	@echo "==================		"
	@echo "cc:				$(CC)		"
	@echo "flags:			$(FLAGS)	"
	@echo "								"

devoptions:
	@echo "HALK build options (development)		"
	@echo "================================		"
	@echo "cc:				$(CC)							"
	@echo "flags:			$(DEVFLAGS)					"
	@echo "													"

HALK: $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $(TMPBIN)

dev: $(OBJS)
	@make devoptions
	$(CC) $(OBJS) $(DEVFLAGS) -o $(TMPBIN)

install:
	make
	cp ./$(BIN).out $(BINDIR)/$(BIN)

uninstall:
	rm -f $(BINDIR)/$(BIN)

clean:
	rm -f $(TMPBIN) src/*.o

%.o: %.c include/%.h
	$(CC) -c $(FLAGS) $< -o $@

# fun
me:
	@[ "$(USER)" = "root" ] && echo "Okay." || echo "What? Make it yourself."

a sandwich:
	@exit

.PHONY: all options devoptions dev install uninstall clean
