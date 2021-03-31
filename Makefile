RUN=g++
CFLAGS=-std=c++20 -g -c
LIBRARIES=-lsfml-graphics -lsfml-window -lsfml-system
SOURCES=main.cpp sector.cpp walls.cpp room.cpp furnitureRoom.cpp map.cpp renderMap.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXEC=run

all: $(SOURCES) $(EXEC)

$(EXEC): $(OBJECTS)
	$(RUN) $(LIBRARIES) $(OBJECTS) -o $(EXEC)

.cpp.o:
	$(RUN) $(CFLAGS) $<

clean:
	rm -rf *.o $(EXEC)
