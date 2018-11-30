CC ?= gcc

# Use the C99 standard
CFLAGS += -std=c99

# Enable additional warnings
CFLAGS += -Wall -Wextra -Werror

# Do not echo build commands
.SILENT:

.PHONY: all build

all: build run

build: project.exe

run: project.exe
	./$<

project.exe: main.o
	$(CC) $(CFLAGS) $^ -o $@
