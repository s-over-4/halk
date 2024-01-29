BIN        := halk
PREFIX     := /usr/local/bin
CC         := gcc
REG_CFLAGS := -std=c99 -O3 -s
DBG_CFLAGS := -std=c99 -Og -ggdb -pedantic 
DBG_CFLAGS += -Wall -Wextra -Wformat -Wpedantic
DBG_CFLAGS += -fsanitize=leak,address,undefined -fno-omit-frame-pointer
CFLAGS     := $(REG_CFLAGS)
SRCS       := $(wildcard src/*.c)
SRCS       := $(filter-out %doer.c,$(SRCS))	# Filter out incomplete doer for now.
OBJS       := $(SRCS:.c=.o)
TEST_SRCS  := $(wildcard test/*.c)
TEST_OUTS  := $(TEST_SRCS:.c=.out)

.PHONY: all reg_options dbg_options halk dbg install uninstall clean test me a sandwich

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
dbg: dbg_options $(OBJS)
	$(CC) $(OBJS) $(DBG_CFLAGS) -o $(BIN).out

test: clean dbg $(TEST_OUTS)
	set -e
	for f in $(TEST_OUTS); do ./$$f; done

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.out: %.c
	$(CC) $< $(filter-out %main.o,$(OBJS)) -o $@ $(CFLAGS)

install: all
	mkdir -p $(PREFIX)
	cp -f $(BIN).out $(PREFIX)/$(BIN)
	chmod 755 $(PREFIX)/$(BIN)

uninstall:
	rm -f $(PREFIX)/$(BIN)

clean:
	rm -f $(BIN).out src/*.o test/*.out

me a:
	@exit

sandwich:
	@[ "$(shell id -u)" = 0 ] && echo "Okay." || echo "What? Make it yourself."
