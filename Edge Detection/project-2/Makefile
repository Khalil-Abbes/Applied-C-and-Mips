###
# Modified Makefile for MinGW on Windows
# Note: This file won't work on WSL or Linux.
DEBUG     = -O0 -g
CFLAGS   += -std=c11 -Wextra -Wall -pedantic -Werror -Wshadow
CFLAGS   += ${DEBUG}
LDFLAGS  += -lm
FLAGS    += ${CFLAGS} ${LDFLAGS}

SRC_DIR    = src
BIN_DIR    = bin
TEST_DIR   = test
BUILD_DIR  = build

SOURCES      = $(wildcard ${SRC_DIR}/*.c)
OBJECTS      = $(patsubst ${SRC_DIR}/%.c,${BUILD_DIR}/%.o,${SOURCES})

LIBS         = ${BIN_DIR}/image.so ${BIN_DIR}/convolution.so ${BIN_DIR}/derivation.so ${BIN_DIR}/main.so
CC = gcc


.PHONY: clean tests

all: ${BUILD_DIR} ${BIN_DIR} ${BIN_DIR}/edgedetection ${LIBS}

${BUILD_DIR}:
	mkdir ${BUILD_DIR}

${BIN_DIR}:
	mkdir ${BIN_DIR}

${BUILD_DIR}/%.o: ${SRC_DIR}/%.c
	-$(CC) $< -c ${CFLAGS} -o $@

${BIN_DIR}/edgedetection: ${OBJECTS}
	-$(CC) -o ${BIN_DIR}/edgedetection ${CFLAGS} ${OBJECTS} ${LDFLAGS}

${BIN_DIR}/image.so: ${SRC_DIR}/image.c
	-$(CC) -shared -fPIC -o ${BIN_DIR}/image.so ${CFLAGS} ${LDFLAGS} ${SRC_DIR}/image.c

${BIN_DIR}/convolution.so: ${SRC_DIR}/convolution.c ${SRC_DIR}/image.c
	-$(CC) -shared -fPIC -o ${BIN_DIR}/convolution.so ${CFLAGS} ${LDFLAGS} ${SRC_DIR}/convolution.c ${SRC_DIR}/image.c

${BIN_DIR}/derivation.so: ${SRC_DIR}/derivation.c ${SRC_DIR}/convolution.c ${SRC_DIR}/image.c
	-$(CC) -shared -fPIC -o ${BIN_DIR}/derivation.so ${CFLAGS} ${LDFLAGS} ${SRC_DIR}/derivation.c ${SRC_DIR}/convolution.c ${SRC_DIR}/image.c

${BIN_DIR}/main.so: ${SOURCES}
	-$(CC) -shared -fPIC -o ${BIN_DIR}/main.so ${CFLAGS} ${LDFLAGS} ${SOURCES}

tests: ${LIBS}
	python3 ${TEST_DIR}/run-tests.py

clean:
	powershell Remove-Item -Recurse -ErrorAction Ignore ${BIN_DIR}, ${BUILD_DIR}
