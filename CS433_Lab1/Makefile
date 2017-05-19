CC = g++
CFLAGS = -c -std=c++11 -O2
LDFLAGS =
SOURCES = Main.cpp MinHeap.cpp ReadyQueue.cpp PCB.cpp PCB_Table.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = assign1

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
