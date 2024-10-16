CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.
LDFLAGS = -ldl

SOURCES = Calculator.cpp ExpressionParser.cpp

OBJECTS = $(SOURCES:.cpp=.o)

TARGET = calc

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean