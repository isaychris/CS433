CC = g++
CFLAGS = -c -std=c++11 -O2
LDFLAGS =
SOURCES = main.cpp event.cpp process.cpp random.cpp scheduler_FCFS.cpp scheduler_SJF.cpp simulation.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = assign3

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
