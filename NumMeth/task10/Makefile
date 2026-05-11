CXX = g++
CXXFLAGS = -std=c++17
TARGET = prog

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) in.txt out.txt

.PHONY: run clean