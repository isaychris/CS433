CC = g++
CFLAGS = -c -std=c++11 -O2
LDFLAGS =
SOURCES = main.cpp simulation.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = assign5

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
