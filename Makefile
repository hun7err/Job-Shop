TARGET=job-shop
CC=gcc

CFLAGS=-c -Wall -g
LINKER=gcc -o
LFLAGS=
LDLIBS=

SRCDIR=src
INCLDIR=include
OBJDIR=obj
BINDIR=bin

SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCLDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm=rm -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS) $(LDLIBS)
	@echo "Biblioteki zlinkowane"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Skompilowano $<"

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Wyczyszczono"

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Usunieto binarke"
