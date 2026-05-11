# Настройки компилятора
CXX = g++
CXXFLAGS = -O3 -Wall -std=c++11
PYTHON = python3

# Имена файлов
TARGET = solver
SRC = main.cpp
DATA = results.txt convergence.txt
SCRIPT = plot.py

# Правило по умолчанию: собрать, запустить расчет и построить графики
all: run plot

# Компиляция C++
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Запуск вычислений (генерация файлов .txt)
run: $(TARGET)
	./$(TARGET)

# Запуск визуализации
plot: $(DATA)
	$(PYTHON) $(SCRIPT)

# Очистка проекта
clean:
	rm -f $(TARGET) $(DATA)
	@echo "Files cleaned."

.PHONY: all run plot clean