NAME				:= HALK
PREFIX			:= /usr/local
BINDIR			:= $(PREFIX)/bin
BIN 				:= $(shell echo $(NAME) | tr '[:upper:]' '[:lower:]')
TMPBIN			:= $(BIN).out
CC					:= gcc
FLAGS				:= -O3 -s
DEVFLAGS			:= -g -ggdb -fsanitize=leak,address,undefined -fno-omit-frame-pointer
SRCS 				:= $(wildcard src/*.c)
SRCS 				:= $(filter-out src/parser.c, $(SRCS)) # exclude the incomplete parser for now.
OBJS 				:= $(SRCS:.c=.o)

all: options HALK

options:
	@$(eval $@_TITLE := "$(NAME) build options")
	@$(eval $@_ULINE := $(shell echo "$($@_TITLE)" | tr '[:print:]' '='))
	@echo "$($@_TITLE)"
	@echo "$($@_ULINE)"
	@echo "cc:            $(CC)"
	@echo "flags:         $(FLAGS)"
	@echo ""

devoptions:
	@$(eval $@_TITLE := "$(NAME) build options \(development\)")
	@$(eval $@_ULINE := $(shell echo "$($@_TITLE)" | tr '[:print:]' '='))
	@echo "$($@_TITLE)"
	@echo "$($@_ULINE)"
	@echo "cc:           $(CC)"
	@echo "flags:        $(DEVFLAGS)"
	@echo ""

HALK: $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $(TMPBIN)

dev: devoptions $(OBJS)
	$(CC) $(OBJS) $(DEVFLAGS) -o $(TMPBIN)

install:
	make
	cp ./$(BIN).out $(BINDIR)/$(BIN)

uninstall:
	rm -f $(BINDIR)/$(BIN)

clean:
	rm -f $(TMPBIN) src/*.o

%.o: %.c include/%.h
	$(CC) -c $(DEVFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $(DEVFLAGS) $< -o $@

me:
	@[ "$(USER)" = "root" ] && echo "Okay." || echo "What? Make it yourself."

a sandwich:
	@exit

.PHONY: all options devoptions dev install uninstall clean
