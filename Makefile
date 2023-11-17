BIN        := halk
PREFIX     := /usr/local/bin
CC         := gcc
REG_CFLAGS := -std=c99 -O3 -s
DBG_CFLAGS := -std=c99 -Og -ggdb -pedantic 
DBG_CFLAGS += -Wall -Wno-deprecated-declarations 
DBG_CFLAGS += -fsanitize=leak,address,undefined -fno-omit-frame-pointer
CFLAGS     := ${REG_CFLAGS}
SRCS       := $(wildcard src/*.c)
OBJS       := $(SRCS:.c=.o)

.PHONY: all reg_options dbg_options halk dbg install uninstall clean me a sandwich

all: halk

reg_options:
	@echo "HALK build options:"
	@echo "CC:         ${CC}"
	@echo "CFLAGS:     ${REG_CFLAGS}"
	@echo

dbg_options:
	@echo "HALK build options (dbg):"
	@echo "CC:         ${CC}"
	@echo "CFLAGS:     ${DBG_CFLAGS}"
	@echo

%.o: %.c
	${CC} -c $< -o $@

halk: reg_options ${OBJS}
	${CC} ${OBJS} ${REG_CFLAGS} -o ${BIN}.out

dbg: CFLAGS := ${DBG_CFLAGS}
dbg: dbg_options ${OBJS}
	${CC} ${OBJS} ${DBG_CFLAGS} -o ${BIN}.out

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
	@[ "${USER}" = "root" ] && echo "Okay." || echo "What? Make it yourself."
