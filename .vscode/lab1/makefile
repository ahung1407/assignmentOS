# Compiler and flags
CC = gcc
CFLAGS = -g -Wall

# Executable name
TARGET = calc

# Source files
SRCS = calc.c operation.c
OBJS = $(SRCS:.c=.o)

# Default target to build the program
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove generated files
clean:
	rm -f $(OBJS) $(TARGET)