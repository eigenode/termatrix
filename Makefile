# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra #-std=c11

# Project structure
SRC_DIR = .
BUILD_DIR = build
TARGET = tmatrix

# Source files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/termatrix.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Default build
all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Object build rule
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if missing
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Run program
run: all
	./$(TARGET)

# Cleanup
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean run
