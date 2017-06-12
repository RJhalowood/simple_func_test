CC = gcc
CFLAGS = -g -Wall
LIBS = -lpcap
OBJS = main7.o 
TARGET = main7

all:${OBJS}
	${CC} ${CFLAGS} -o ${TARGET} $^ ${LIBS}

${OBJS}:main7.c
	${CC} ${CFLAGS} -c $^ -o $@ ${LIBS}

clean:
	-rm -f  *.o ${TARGET}


