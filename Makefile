TARGET=job-shop
CC=g++

CFLAGS=-c -Wall -g
LINKER=g++ -o
LFLAGS=
LDLIBS=

SRCDIR=src
INCLDIR=include
OBJDIR=obj
BINDIR=bin

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCLDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm=rm -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	@echo "Linkowanie bibliotek z $<"
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS) $(LDLIBS)
	@echo "Biblioteki zlinkowane"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@echo "Kompilacja $<"
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
