BIN        := halk
PREFIX     := /usr/local/bin
CC         := gcc
REG_CFLAGS := -std=c99 -O3 -s
DBG_CFLAGS := -Og -ggdb -pedantic -Wall -Wno-deprecated-declarations -fsanitize=leak,address,undefined -fno-omit-frame-pointer
CFLAGS     := ${REG_CFLAGS}
SRCS       := $(wildcard src/*.c)
# SRCS       := $(filter-out src/parser.c, $(SRCS))
OBJS       := $(SRCS:.c=.o)

all: halk

reg_options:
	@echo "HALK build options:"
	@echo "CC:         ${CC}"
	@echo "REG_CFLAGS: ${REG_CFLAGS}"
	@echo

dbg_options:
	@echo "HALK build options (dbg):"
	@echo "CC:         ${CC}"
	@echo "DBG_CFLAGS: ${DBG_CFLAGS}"
	@echo

halk: reg_options ${OBJS}
	${CC} ${OBJS} ${REG_CFLAGS} -o ${BIN}.out

dbg: CFLAGS += ${DBG_CFLAGS}
dbg: dbg_options ${OBJS}
	${CC} ${OBJS} ${DBG_CFLAGS} -o ${BIN}.out

%.o: %.c include/%.h
	${CC} -c ${CFLAGS} $< -o $@

install: all
	mkdir -p ${PREFIX}
	cp -f ${BIN}.out ${PREFIX}/${BIN}
	chmod 755 ${PREFIX}/${BIN}

uninstall:
	rm -f ${PREFIX}/${BIN}

clean:
	rm -f ${BIN}.out src/*.o

me a:
	@exit

sandwich:
	@[ "$(USER)" = "root" ] && echo "Okay." || echo "What? Make(1) it yourself."

.PHONY: all reg_options dbg_options dbg install uninstall clean 
