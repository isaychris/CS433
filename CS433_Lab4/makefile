CC = g++ -lpthread
CFLAGS = -c -O2 
LDFLAGS =
SOURCES = main.cpp buffer.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = assign4

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
