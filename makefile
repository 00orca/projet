CC=gcc
FLAGS =-Wall -g
SDL_DIR=${HOME}/projet/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include/
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf -lm
INCS=-I${SDL_INC_DIR}
PROG=main

all: sdl_text clean

sdl_text: main.c
	${CC} -c main.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c interface.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c piece.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -o main main.o interface.o piece.o ${LIBS} ${INCS} ${FLAGS}

clean:
	rm -f *.o

cleanall:
	clean rm -f ${PROG}
