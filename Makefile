CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Iinclude
TARGET := dungeon_escape
SOURCE := src/main.cpp

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCE) include/Game.h include/Dungeon.h include/Room.h include/Player.h include/Enemy.h include/Treasure.h
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
