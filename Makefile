# Use gcc if no other compiler is set
CC ?= gcc

# Use the C99 standard
CFLAGS += -std=c99

# Enable additional warnings
CFLAGS += -Wall -Wextra -Werror

# This Make function is used to run a test binary
define run-test
$(1)

endef


SRCS := $(wildcard *.c)

LIB_SRCS := $(filter-out main.c %_test.c,$(SRCS))
TEST_SRCS := $(filter %_test.c,$(SRCS))

HDRS := $(wildcard *.h)

LIB_OBJS := $(patsubst %.c,build/%.o,$(LIB_SRCS))

UNIT_TESTS := $(patsubst %_test.c,%,$(TEST_SRCS))
UNIT_TESTS_BIN := $(patsubst %,build/%_test.exe,$(UNIT_TESTS))

# Do not echo build commands
.SILENT:

.PHONY: all compile run test clean

all: compile test run

compile: $(LIB_OBJS)

test: $(UNIT_TESTS_BIN)
	$(foreach test,$(UNIT_TESTS_BIN),$(call run-test,./$(test)))

run: build/project.exe
	./$<

clean:
	-rm -r build

build:
	mkdir build

build/%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

build/%_test.exe: build/%_test.o $(LIB_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

build/project.exe: build/main.o
	$(CC) $(CFLAGS) $^ -o $@
