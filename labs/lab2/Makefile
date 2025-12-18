# Compiler and flags
CC = gcc
CFLAGS = -Wall -O2 -MMD -MP
SRC_DIR = src
OBJ_DIR = tmp
BIN_DIR = out

# Source files
SRC_COMMON = $(SRC_DIR)/curr_time.c
SRC_CREATE = $(SRC_DIR)/sem_create.c
SRC_GETINFO = $(SRC_DIR)/sem_get_info.c
SRC_OP = $(SRC_DIR)/sem_op.c

# Object files
OBJ_COMMON = $(OBJ_DIR)/curr_time.o
OBJ_CREATE = $(OBJ_DIR)/sem_create.o
OBJ_GETINFO = $(OBJ_DIR)/sem_get_info.o
OBJ_OP = $(OBJ_DIR)/sem_op.o

# Executable names
BIN_CREATE = $(BIN_DIR)/sem_create
BIN_GETINFO = $(BIN_DIR)/sem_get_info
BIN_OP = $(BIN_DIR)/sem_op

# Default target
all: dirs $(BIN_CREATE) $(BIN_GETINFO) $(BIN_OP)

dirs:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Link executables
$(BIN_CREATE): $(OBJ_CREATE)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_GETINFO): $(OBJ_GETINFO)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_OP): $(OBJ_OP) $(OBJ_COMMON)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean dirs
