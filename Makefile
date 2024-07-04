CXX = g++ 
CXXFLAGS = -Wall -std=c++17 \
           -IC:/msys64/ucrt64/include/SDL2 \
           -D_REENTRANT

LDFLAGS = -LC:/msys64/ucrt64/lib \
          -lSDL2 -lSDL2_image -lSDL2_ttf

SOURCES = $(wildcard src/*.cpp) 
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = main  # Nombre del ejecutable final

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
