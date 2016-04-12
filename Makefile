INCDIR = include/lotalanta
SRCDIR = src/lotalanta
_OBJDIR = obj
OBJDIR := $(_OBJDIR)/lotalanta

MKDIR_P = mkdir -p

LFLAGS = -Wall
CFLAGS = -Wall -c -O0 --std=c++11 -g
CC = clang++
COMPILE = $(CC) $(CFLAGS)
LINK = $(CC) $(LFLAGS)

_OBJS = Building.o City.o Concave.o Court.o DirectionMappings.o Point.o Walkway.o Runicinnya.o
OBJS = $(patsubst %, $(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.h
	$(OBJDST)
	$(COMPILE) -c -o $@ $<

all: lotalanta

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	$(MKDIR_P) $(OBJDIR)

lotalanta: $(OBJS)
	$(LINK) -o $@ $^

.PHONY: clean

clean:
	rm -rf $(_OBJDIR)
