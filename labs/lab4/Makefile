# --- Configuration ---
SRC_DIR := src
OBJ_DIR := tmp
OUT_DIR := out

CC := gcc
CFLAGS := -Wall -O2 -MMD -MP

# --- Source files ---
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
DEPS := $(OBJS:.o=.d)

# --- Programs that contain main() ---
MAINS := $(shell grep -l "^[[:space:]]*int[[:space:]]\+main" $(SRC) 2>/dev/null || true)
EXECS := $(patsubst $(SRC_DIR)/%,$(OUT_DIR)/%,$(basename $(MAINS)))

# --- Default target ---
all: $(EXECS)

# --- Link each executable with binary_sems.o ---
$(OUT_DIR)/%: $(OBJ_DIR)/%.o $(OBJ_DIR)/binary_sems.o | $(OUT_DIR)
	@echo "Linking $@ ..."
	$(CC) $(CFLAGS) -o $@ $^

# --- Compile object files ---
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling $< ..."
	$(CC) $(CFLAGS) -c $< -o $@

# --- Create directories ---
$(OBJ_DIR) $(OUT_DIR):
	mkdir -p $@

# --- Helper targets ---
list:
	@echo "Executables to be built:"
	@for exe in $(EXECS); do echo "  $$exe"; done

run: all
ifndef NAME
	$(error Usage: make run NAME=program)
endif
	@exe="$(OUT_DIR)/$(NAME)"; \
	if [ -x "$$exe" ]; then \
	  echo "Running $$exe ..."; \
	  "$$exe"; \
	else \
	  echo "Executable $$exe not found!"; exit 1; \
	fi

clean:
	rm -rf $(OBJ_DIR) $(OUT_DIR)

-include $(DEPS)
