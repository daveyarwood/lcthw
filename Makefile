CC=cc
CFLAGS=-Wall -g

SOURCE_FILES := $(wildcard *.c)
COMPILED := $(addprefix target/, $(basename $(SOURCE_FILES)))

all: $(COMPILED)

target/%: %.c | target
	$(CC) $(CFLAGS) $^ -o $@

target:
	mkdir -p target

clean:
	rm -rf target
