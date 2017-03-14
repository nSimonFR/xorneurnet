# Makefile

CC=gcc

CFLAGS= -Wall -Wextra -std=c99 -lm

SRC= neuralnet.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: main

main: ${OBJ} neuralnet

debug: CFLAGS+= -O0 -g
debug: main

clean:
	rm -f ${OBJ} ${DEP}
	rm -f main

# END
