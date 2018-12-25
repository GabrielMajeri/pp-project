# Use the C99 standard
CFLAGS += -std=c99

# Enable additional warnings
CFLAGS += -Wall -Wextra -Werror

# Enable optimizations
CFLAGS += -O

# This Make function is used to run a test binary
define run-test
$(1)

endef


SRCS := $(wildcard src/*.c)

LIB_SRCS := $(filter-out src/main.c src/%_test.c,$(SRCS))
TEST_SRCS := $(filter src/%_test.c,$(SRCS))

HDRS := $(wildcard src/*.h)

LIB_OBJS := $(patsubst src/%.c,build/%.o,$(LIB_SRCS))

UNIT_TESTS := $(patsubst src/%_test.c,%,$(TEST_SRCS))
UNIT_TESTS_BIN := $(patsubst %,build/%_test.exe,$(UNIT_TESTS))

# Do not echo build commands
.SILENT:

.PHONY: all compile run test clean

all: compile test

compile: build/project.exe $(LIB_OBJS)

test: $(UNIT_TESTS_BIN)
	$(foreach test,$(UNIT_TESTS_BIN),$(call run-test,./$(test)))

run: build/project.exe
	./$<

clean:
	-rm -r build

build:
	mkdir build

build/%.o: src/%.c $(HDRS) | build
	gcc $(CFLAGS) -c $< -o $@

build/%_test.exe: build/%_test.o $(LIB_OBJS)
	gcc $(CFLAGS) $^ -o $@ -lm

build/project.exe: build/main.o $(LIB_OBJS)
	gcc $(CFLAGS) $^ -o $@ -lm
