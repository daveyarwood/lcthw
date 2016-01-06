CC=cc
CFLAGS=-Wall -g

EXCEPTIONS := object.c ex19.c ex22.c ex22_main.c
SOURCE_FILES := $(filter-out $(EXCEPTIONS), $(wildcard *.c))
COMPILED := $(addprefix target/, $(basename $(SOURCE_FILES)))

all: $(COMPILED) target/ex19 target/ex22_main

target/ex19: target/objects/object.o | target

target/ex22_main: target/objects/ex22.o | target

target/objects/%.o: %.c | target
	$(CC) $(CFLAGS) $^ -c -o $@

target/%: %.c | target
	$(CC) $(CFLAGS) $^ -o $@

target:
	mkdir -p target
	mkdir -p target/objects

clean:
	rm -rf target
