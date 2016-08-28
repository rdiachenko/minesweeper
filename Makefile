SOURCES = *.cpp
CC = g++
COMPILER_FLAGS = -std=c++11 -Wall -Werror
LINKER_FLAGS = -lSDL2 -lSDL2_image
EXECUTABLE = minesweeper

all:
	$(CC) $(SOURCES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXECUTABLE)

clean:
	rm $(EXECUTABLE)
