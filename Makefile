CC=cc
CFLAGS=-Wall -g

EXCEPTIONS := object.c ex19.c ex22.c ex22_main.c
SOURCE_FILES := $(filter-out $(EXCEPTIONS), $(wildcard *.c))
COMPILED := $(addprefix target/, $(basename $(SOURCE_FILES)))

all: $(COMPILED) target/ex19 target/ex22_main

target/ex19: target/object.o | target

target/ex22_main: target/ex22.o | target

target/%.so: %.o | target
	$(CC) -shared -o $@ $^

target/%.o: %.c | target
	$(CC) $(CFLAGS) $^ -c -o $@

target/%: %.c | target
	$(CC) $(CFLAGS) $^ -o $@

target:
	mkdir -p target

clean:
	rm -rf target
