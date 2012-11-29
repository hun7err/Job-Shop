TARGET=job-shop
CC=g++

CFLAGS=-c -Wall -g
LINKER=g++ -o
LFLAGS=
LDLIBS=-lrt

SRCDIR=src
INCLDIR=include
OBJDIR=obj
BINDIR=bin

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCLDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm=rm -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	@echo "LD $(LINKER) $@ $(LFLAGS) $(OBJECTS) $(LDLIBS)"
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS) $(LDLIBS)
	@echo "LD Linking successful!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@echo "CC $(CC) $< -o $@"
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Wyczyszczono"

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Usunieto binarke"
