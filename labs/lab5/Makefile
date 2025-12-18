# --- CONFIG ---
ROOT := .
OBJDIR := tmp
OUTDIR := out

CC  := gcc
CXX := g++
CFLAGS   := -Wall -O2 -MMD -MP
CXXFLAGS := -Wall -O2 -MMD -MP

# --- SOURCES ---
SRC_ROOT := $(wildcard $(ROOT)/*.c $(ROOT)/*.cc $(ROOT)/*.cpp $(ROOT)/*.cxx)
SRC_WR   := $(wildcard $(ROOT)/writer-reader/*.c $(ROOT)/writer-reader/*.cc $(ROOT)/writer-reader/*.cpp $(ROOT)/writer-reader/*.cxx)
SRC := $(SRC_ROOT) $(SRC_WR)

# --- OBJECT FILES ---
OBJS_ROOT := $(patsubst $(ROOT)/%, $(OBJDIR)/%, $(SRC_ROOT:.c=.o))
OBJS_ROOT := $(OBJS_ROOT:.cpp=.o)
OBJS_ROOT := $(OBJS_ROOT:.cc=.o)
OBJS_ROOT := $(OBJS_ROOT:.cxx=.o)

OBJS_WR := $(patsubst $(ROOT)/%, $(OBJDIR)/%, $(SRC_WR:.c=.o))
OBJS_WR := $(OBJS_WR:.cpp=.o)
OBJS_WR := $(OBJS_WR:.cc=.o)
OBJS_WR := $(OBJS_WR:.cxx=.o)

OBJS := $(OBJS_ROOT) $(OBJS_WR)
DEPS := $(OBJS:.o=.d)

# --- Find mains ---
MAINS_ROOT := $(shell grep -l "^[[:space:]]*int[[:space:]]\+main" $(SRC_ROOT) 2>/dev/null || true)
MAINS_WR   := $(shell grep -l "^[[:space:]]*int[[:space:]]\+main" $(SRC_WR) 2>/dev/null || true)

EXECS_ROOT := $(patsubst $(ROOT)/%, $(OUTDIR)/%,$(basename $(MAINS_ROOT)))
EXECS_WR   := $(patsubst $(ROOT)/writer-reader/%, $(OUTDIR)/writer-reader/%,$(basename $(MAINS_WR)))
EXECS := $(EXECS_ROOT) $(EXECS_WR)

# --- Non-main objects ---
OBJS_ROOT_NO_MAIN := $(filter-out $(patsubst $(ROOT)/%, $(OBJDIR)/%,$(MAINS_ROOT:.c=.o) $(MAINS_ROOT:.cpp=.o) $(MAINS_ROOT:.cc=.o) $(MAINS_ROOT:.cxx=.o)),$(OBJS_ROOT))
OBJS_WR_NO_MAIN   := $(filter-out $(patsubst $(ROOT)/writer-reader/%, $(OBJDIR)/writer-reader/%,$(MAINS_WR:.c=.o) $(MAINS_WR:.cpp=.o) $(MAINS_WR:.cc=.o) $(MAINS_WR:.cxx=.o)),$(OBJS_WR))

# --- DEFAULT TARGET ---
all: $(EXECS)

# --- EXECUTABLE BUILD RULES ---
# Root executables
$(OUTDIR)/%: $(OBJDIR)/%.o $(OBJS_ROOT_NO_MAIN) | $(OUTDIR)
	@echo "Linking $@ ..."
	$(CC) $(CFLAGS) -o $@ $^

# writer-reader executables
$(OUTDIR)/writer-reader/%: $(OBJDIR)/writer-reader/%.o $(OBJS_WR_NO_MAIN) | $(OUTDIR)/writer-reader
	@echo "Linking $@ ..."
	$(CC) $(CFLAGS) -o $@ $^

# --- COMPILE RULES ---
$(OBJDIR)/%.o: $(ROOT)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(ROOT)/%.cc | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(ROOT)/%.cpp | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(ROOT)/%.cxx | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- DIRECTORIES ---
$(OBJDIR) $(OUTDIR) $(OUTDIR)/writer-reader:
	mkdir -p $@

# --- LIST EXECUTABLES ---
list:
	@echo "Executables:"
	@for exe in $(EXECS); do echo "  $$exe"; done

# --- RUN TARGET ---
run: all
ifndef NAME
	$(error Usage: make run NAME=program)
endif
	@exe="$(OUTDIR)/$(NAME)"; \
	if [ -x "$$exe" ]; then \
	  echo "Running $$exe ..."; \
	  "$$exe"; \
	else \
	  echo "Executable $$exe not found!"; exit 1; \
	fi

# --- CLEAN ---
clean:
	rm -rf $(OBJDIR) $(OUTDIR)

-include $(DEPS)
