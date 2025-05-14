CXX = g++
CXXFLAGS = -std=c++20 -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -Wsign-compare
SOURCES = main.cpp resources/Map.cpp resources/Pacman.cpp resources/Ghost.cpp resources/Blinky.cpp resources/Pinky.cpp resources/Inky.cpp resources/Clyde.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = app

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

