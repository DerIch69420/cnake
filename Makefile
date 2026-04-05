# Complier and flags
CC := cc
CFLAGS := -std=c99 -Wall -Werror -pedantic
OPTFLAGS := -O3

# Directories
SRC_DIR := src
OBJ_DIR := object
BIN_DIR := bin

# Executable name
TARGET := $(BIN_DIR)/cnake

# Source and object files
SRC := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/game/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Default target
all: build

# Normal build
build: CFLAGS += 
build: prepare $(TARGET)

# Optimized build
optimized: CFLAGS += $(OPTFLAGS)
optimized: prepare $(TARGET)

# Prepare directories
prepare:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	@echo "Directories prepared"

# Build executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lncurses $(CFLAGS)
	@echo "Cnake generated into $(TARGET)"


# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)
	@echo "Compiled $< -> $@"

# Clean up
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)
	@echo "Cleaned up"

.PHONY: all build optimized clean prepare
