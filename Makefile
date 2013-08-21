CFLAGS=-std=c99
SOURCE=tictactoe.c
APP=tictactoe

all:
	gcc ${CFLAGS} -o ${APP} ${SOURCE}
clean:
	rm ${APP}
