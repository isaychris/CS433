CC = g++
CFLAGS = -c -O2
LDFLAGS =
SOURCES = Main.cpp Shell.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = assign2

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
