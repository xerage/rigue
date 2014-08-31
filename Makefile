TARGET = rigue

VERBOSE = @

SRCDIR = src

SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=%.o) 

CC = gcc

CFLAGS = -Os -pedantic -Wall -lX11 -c
LFLAGS = -Wall -lX11

all: $(TARGET)

$(OBJECTS): %.o : $(SRCDIR)/%.c
	$(VERBOSE)$(CC) $(CFLAGS) -c $< -o $@
	@echo Compiled $< successfully!

$(TARGET): $(OBJECTS)
	$(VERBOSE)$(CC) $(LFLAGS) $(OBJECTS) -o $(TARGET)
	@echo Linking complete!

clean:
	$(VERBOSE)rm -f rigue *.o *~
	@echo Cleanup complete!

tar:
	@echo Archiving:
	$(VERBOSE)tar cvf rigue.tar src/*
	@echo Archive $(TARGET).tar created!

install:
	$(VERBOSE)cp -f rigue /usr/bin/
	@echo $(TARGET) installed!

info:
	@echo Some info:
	@echo Preprocessing with: $(CC) $(CFLAGS) -o OUT
	@echo Compiling C with: $(CC) $(CFLAGS) -o OUT
	@echo Linking with: $(CC) $(LFLAGS) -o OUT
