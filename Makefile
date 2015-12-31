CC=cc
CFLAGS=-Wall -g

SOURCE_FILES := $(filter-out object.c ex19.c, $(wildcard *.c))
COMPILED := $(addprefix target/, $(basename $(SOURCE_FILES)))

all: $(COMPILED) target/ex19

target/ex19: target/objects/object.o | target

target/objects/%.o: %.c | target
	$(CC) $(CFLAGS) $^ -c -o $@

target/%: %.c | target
	$(CC) $(CFLAGS) $^ -o $@

target:
	mkdir -p target
	mkdir -p target/objects

clean:
	rm -rf target
