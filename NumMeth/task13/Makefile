CXX = g++
CXXFLAGS = -std=c++17
TARGET = program
SOURCES = main.cpp R2_interpol.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Assembling the program
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Ready! Run: ./$(TARGET)"

# Cleaning
clean:
	rm -f $(TARGET)

# Launch
run: $(TARGET)
	./$(TARGET)

.PHONY: clean run