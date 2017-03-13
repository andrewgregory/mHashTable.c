# the tap.c submodule must be checked out to build and run tests

CFLAGS += -Wall -Wextra -g -I..

PROVE = prove --exec ./runtest

TESTS = 01-sanity.t 10-basic.t 10-collision.t 90-smoke.t

01-sanity.t: CFLAGS += -std=c99 -pedantic -Werror

%.t: %.c ../mhashtable.c ../mhashtable.h tap.c/tap.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

check: tests
	$(PROVE) $(TESTS)

gcov: CC = gcc
gcov: CFLAGS += -fprofile-arcs -ftest-coverage
gcov: check
	gcov $(TESTS)

gprof: CC = gcc
gprof: CFLAGS += -pg
gprof: check

memcheck: PROVE += --exec 'valgrind --leak-check=full --error-exitcode=99 --quiet'
memcheck: check

tests: $(TESTS)

all: tests

clean:
	$(RM) $(TESTS)
	$(RM) *.gcov *.gcda *.gcno gmon.out

.PHONY: all clean check gcov gprof tests
