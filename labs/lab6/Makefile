# ---------- CONFIG ----------
ROOT := .
OBJDIR := tmp
OUTDIR := out

CC := gcc
CFLAGS := -Wall -O2 -MMD -MP -pthread

# ---------- SOURCES ----------
SRC := $(wildcard $(ROOT)/*.c)

# ---------- OBJECTS ----------
OBJS := $(patsubst $(ROOT)/%.c,$(OBJDIR)/%.o,$(SRC))
DEPS := $(OBJS:.o=.d)

# ---------- EXECUTABLES ----------
EXECS := $(patsubst $(ROOT)/%.c,$(OUTDIR)/%,$(SRC))

# ---------- DEFAULT ----------
all: $(EXECS)

# ---------- LINK ----------
$(OUTDIR)/%: $(OBJDIR)/%.o | $(OUTDIR)
	@echo "Linking $@"
	$(CC) $(CFLAGS) -o $@ $<

# ---------- COMPILE ----------
$(OBJDIR)/%.o: $(ROOT)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# ---------- DIRS ----------
$(OBJDIR) $(OUTDIR):
	mkdir -p $@

# ---------- CLEAN ----------
clean:
	rm -rf $(OBJDIR) $(OUTDIR)

-include $(DEPS)
