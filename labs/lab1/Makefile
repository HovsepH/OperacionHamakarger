# --- Կոնֆիգ ---
FOLDER ?= src
OBJDIR := tmp
OUTDIR := out

CXX := g++
CC  := gcc
CXXFLAGS := -Wall -O2 -MMD -MP
CFLAGS   := -Wall -O2 -MMD -MP

# --- Աղբյուրներ ---
SRC := $(wildcard $(FOLDER)/*.c $(FOLDER)/*.cc $(FOLDER)/*.cpp $(FOLDER)/*.cxx)

# --- Object ֆայլեր ---
OBJS := $(patsubst $(FOLDER)/%, $(OBJDIR)/%, $(SRC:.c=.o))
DEPS := $(OBJS:.o=.d)

# --- Գտնում ենք main ունեցող source-երը ---
MAINS := $(shell grep -l "^[[:space:]]*int[[:space:]]\+main" $(SRC) 2>/dev/null || true)

# --- Executables ---
EXECS := $(patsubst $(FOLDER)/%,$(OUTDIR)/%,$(basename $(MAINS)))

# Լռելյայն թիրախ
all: $(EXECS)

# Յուրաքանչյուր executable = իր main.o + բոլոր non-main.o-ները
$(OUTDIR)/%: $(OBJDIR)/%.o $(filter-out $(patsubst $(FOLDER)/%,$(OBJDIR)/%,$(MAINS:.c=.o) $(MAINS:.cpp=.o) $(MAINS:.cc=.o) $(MAINS:.cxx=.o)),$(OBJS)) | $(OUTDIR)
	@echo "Linking $@ ..."
	$(CXX) $(CXXFLAGS) -o $@ $^

# --- Compile կանոններ ---
$(OBJDIR)/%.o: $(FOLDER)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(FOLDER)/%.cc | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(FOLDER)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(FOLDER)/%.cxx | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- Հարմար թագեր ---
list:
	@echo "Executables:"
	@for exe in $(EXECS); do echo "  $$exe"; done

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

# --- Պանակներ ---
$(OBJDIR) $(OUTDIR):
	mkdir -p $@

# --- Մաքրել ---
clean:
	rm -rf $(OBJDIR) $(OUTDIR)

-include $(DEPS)
