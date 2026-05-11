CXX = g++
TARGET = program
SOURCES = main.cpp myfun.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Сборка программы
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)
	@echo "Ready! Run: ./$(TARGET)"

# Компиляция каждого .cpp файла
%.o: %.cpp
	$(CXX) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET)

# Запуск
run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
