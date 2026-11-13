# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -g
CPPFLAGS = -Isrc/client -Isrc/server

# Directories
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Source files
CLIENT_SRC = $(wildcard src/client/*.c)
SERVER_SRC = $(wildcard src/server/*.c)

# Object files
CLIENT_OBJ = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(CLIENT_SRC))
SERVER_OBJ = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SERVER_SRC))

# Dependency files
DEPS = $(CLIENT_OBJ:.o=.d) $(SERVER_OBJ:.o=.d)

# Default target
.PHONY: all client server clean run-client run-server

all: client server

# Build client
client: $(BUILD_DIR)/client

$(BUILD_DIR)/client: $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Build server
server: $(BUILD_DIR)/server

$(BUILD_DIR)/server: $(SERVER_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Compile source files into object files
$(OBJ_DIR)/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

# Run applications
run-client: client
	./$(BUILD_DIR)/client

run-server: server
	./$(BUILD_DIR)/server

# Remove compiled files
clean:
	rm -rf $(BUILD_DIR)

# Include generated header dependencies
-include $(DEPS)
