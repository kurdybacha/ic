CC=g++
CFLAGS=-c -g -Wall -std=c++14
LDFLAGS=
SOURCES=tst_array_utility.cpp array_utility.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tst_array_utility

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm *.o $(EXECUTABLE)
