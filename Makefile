BIN        := halk
PREFIX     := /usr/local/bin
CC         := gcc
REG_CFLAGS := -ansi -O3 -s
DBG_CFLAGS := -ansi -Og -ggdb -pedantic 
DBG_CFLAGS += -Wall -Wextra -Wformat -Werror -Wpedantic
DBG_CFLAGS += -fsanitize=leak,address,undefined -fno-omit-frame-pointer
CFLAGS     := $(REG_CFLAGS)
SRCS       := $(wildcard src/*.c)
SRCS       := $(filter-out %doer.c,$(SRCS))	# Filter out incomplete doer for now.
OBJS       := $(SRCS:.c=.o)

.PHONY: all reg_options dbg_options halk dbg install uninstall clean me a sandwich

all: halk

reg_options:
	@echo "HALK build options:"
	@echo "CC:         $(CC)"
	@echo "CFLAGS:     $(REG_CFLAGS)"
	@echo

dbg_options:
	@echo "HALK build options (dbg):"
	@echo "CC:         $(CC)"
	@echo "CFLAGS:     $(DBG_CFLAGS)"
	@echo

halk: reg_options $(OBJS)
	$(CC) $(OBJS) $(REG_CFLAGS) -o $(BIN).out

dbg: CFLAGS := $(DBG_CFLAGS)
dbg: TEST := -D TEST
dbg: dbg_options $(OBJS)
	$(CC) $(OBJS) $(DBG_CFLAGS) -o $(BIN).out

%.o: %.c
	$(CC) $(TEST) -c $< -o $@

install: all
	mkdir -p $(PREFIX)
	cp -f $(BIN).out $(PREFIX)/$(BIN)
	chmod 755 $(PREFIX)/$(BIN)

uninstall:
	rm -f $(PREFIX)/$(BIN)

clean:
	rm -f $(BIN).out src/*.o

me a:
	@exit
sandwich:
	@[ "$(USER)" = "root" ] && echo "Okay." || echo "What? Make it yourself."
