CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
LDFLAGS = -L./bin/debug -lwd
INCLUDE = -I ./include -I ../ds/include

LIBSRC = ../ds/src/uid.c ../ds/src/task.c ../ds/src/heap.c ../ds/src/hpq.c ../ds/src/hscheduler.c ./src/immortal.c ../ds/src/dvector.c
LIBOBJ = $(LIBSRC:.c=.o)
LIBNAME = libwd.so

.PHONY: all clean

all: ./bin/debug/$(LIBNAME) ./bin/debug/watchdog ./bin/debug/client

./bin/debug/$(LIBNAME): $(LIBOBJ)
	$(CC) -shared -o $@ $^ -lc

./bin/debug/watchdog: ./test/watchdog_test.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $< $(LDFLAGS)

./bin/debug/client: ./test/client.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $< $(LDFLAGS)

../ds/src/%.o: ../ds/src/%.c
	$(CC) $(CFLAGS) -fPIC $(INCLUDE) -c -o $@ $<

./src/%.o: ./src/%.c
	$(CC) $(CFLAGS) -fPIC $(INCLUDE) -c -o $@ $<

clean:
	rm -f $(LIBOBJ) ./bin/debug/$(LIBNAME) ./bin/debug/watchdog ./bin/debug/client

# Set the library path
export LD_LIBRARY_PATH := ./bin/debug:$(LD_LIBRARY_PATH)
