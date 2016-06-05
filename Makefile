SOURCES = *.cpp
CC = g++
COMPILER_FLAGS = -std=c++11
LINKER_FLAGS = -lSDL2
EXECUTABLE = minesweeper

all:
	$(CC) $(SOURCES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXECUTABLE)

clean:
	rm $(EXECUTABLE)