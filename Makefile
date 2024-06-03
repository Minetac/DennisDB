CC = gcc
CFLAGS = -Iinclude -Wall
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
EXECUTABLE = main

# List of all source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

# Generate list of object files from source files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Targets
all: $(BUILD_DIR)/$(EXECUTABLE)

$(BUILD_DIR)/$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each source file into an object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/$(EXECUTABLE)


.PHONY: all clean
