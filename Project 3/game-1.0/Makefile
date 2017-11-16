#
# Simple development makefile
#

#
# add more flags here,
# but don't remove the "+="
#
CFLAGS += -O2 -g -Wall -std=gnu99 #-Wsign-compare -Wfloat-equal -Wformat-security #-Werror
CPPFLAGS +=
LDFLAGS += -lm

OBJECTS = graphics.o game_logic.o character.o


all: game

game: ${OBJECTS}
	${CC} ${CFLAGS} game.c ${OBJECTS} -o game ${LDFLAGS}

clean:
	-rm -f game

install:


.PHONY: all install clean

# end of development makefile
