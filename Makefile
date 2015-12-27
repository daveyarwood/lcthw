CC=cc
CFLAGS=-Wall -g

source_files = $(wildcard *.c)

.PHONY: all $(source_files) clean

all:
	$(MAKE) $(source_files)

$(source_files):
	mkdir -p compiled
	$(CC) $(CFLAGS) $@ -o compiled/$(basename $@)

clean:
	rm -rf compiled
