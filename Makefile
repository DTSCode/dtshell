# /* -*- mode: Makefile; indent-tabs-mode: true; tab-width: 4 -*- */

CC = gcc
VER = c11
CFLAGS = -std=c11 -Wextra -Wall -pedantic -g
CPPFLAGS = -Iinclude
OBJECTS = bin/dtsh.o bin/shell_getline.o bin/shell_execute.o bin/shell_register_signals.o

.PHONY: all clean install run

all: bin/dtsh

bin/dtsh: bin/libdtsh.so
	@LD_LIBRARY_PATH=${PWD}/bin:$LD_LIBRARY_PATH $(CC) -o bin/dtsh -L./bin -ldtsh -lreadline -ldl

bin/libdtsh.so: $(OBJECTS)
	@$(CC) -shared -o bin/libdtsh.so $(OBJECTS)

bin/%.o: src/%.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -fpic -o $@ $<

clean:
	@rm -rf bin/*

install:
	:

run:
	@LD_LIBRARY_PATH=${PWD}/bin:$LD_LIBRARY_PATH bin/dtsh
