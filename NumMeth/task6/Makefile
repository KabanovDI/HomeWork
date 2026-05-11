CXX = g++
CXXFLAGS = -std=c++17
TARGET = program
SOURCES = main.cpp myfun.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Assembling the program
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Ready! Run: ./$(TARGET)"

# Compiling each .cpp file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleaning
clean:
	rm -f $(OBJECTS) $(TARGET)

# Launch
run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
