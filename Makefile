BIN        := halk
PREFIX     := /usr/local/bin
CC         := gcc
REG_CFLAGS := -std=c99 -O3 -s
DBG_CFLAGS := -std=c99 -Og -ggdb -pedantic 
DBG_CFLAGS += -Wall -Wextra -Wformat -Wpedantic
DBG_CFLAGS += -fsanitize=address -fno-omit-frame-pointer -DDBG
CFLAGS     := none
SRCS       := $(wildcard src/*.c)
SRCS       := $(filter-out %stack.c,$(SRCS))	# Filter out unused stack code.
OBJS       := $(SRCS:.c=.o)
TEST_SRCS  := $(wildcard test/*.c)
TEST_OUTS  := $(TEST_SRCS:.c=.out)

.PHONY: all reg_options dbg_options halk dbg install uninstall clean test me a sandwich

all: halk

options:
	@echo "HALK build options:"
	@echo "CC:         $(CC)"
	@echo "CFLAGS:     $(CFLAGS)"
	@echo

halk: CFLAGS := $(REG_CFLAGS)
halk: options $(OBJS)
	$(CC) $(OBJS) $(REG_CFLAGS) -o $(BIN).out

dbg: CFLAGS := $(DBG_CFLAGS)
dbg: clean options $(OBJS)
	$(CC) $(OBJS) $(DBG_CFLAGS) -o $(BIN).out

test: CFLAGS := $(REG_CFLAGS)
test: $(TEST_OUTS)
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
