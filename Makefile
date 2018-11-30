CC ?= gcc

# Use the C99 standard
CFLAGS += -std=c99

# Enable additional warnings
CFLAGS += -Wall -Wextra -Werror

# Do not echo build commands
.SILENT:

.PHONY: all build clean

all: build run

test: xorshift_test.exe
	./xorshift_test.exe

build: project.exe

run: project.exe
	./$<

clean:
	-rm *.exe
	-rm *.o

xorshift_test.exe: xorshift_test.o xorshift.o test_utils.o
	$(CC) $(CFLAGS) $^ -o $@

project.exe: main.o
	$(CC) $(CFLAGS) $^ -o $@
