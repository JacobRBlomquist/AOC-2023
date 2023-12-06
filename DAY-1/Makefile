# subdir1/Makefile
NAME := "DAY-1"
# Compiler
CC := gcc

# Compiler flags
CFLAGS := -Wall -Wextra -std=c99

# Source files
SRC := main.c

# Object files
OBJ := $(SRC:.c=.o)

# Target executable
TARGET := ../output/$(NAME)

# Build rule
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
