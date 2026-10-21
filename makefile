# Компилятор C++
CXX = g++

# Флаги: стандарт C++17, все предупреждения.
# ВАЖНО: -I../include, так как мы будем запускать компилятор из папки build.
CXXFLAGS = -std=c++17 -Wall -Wextra -I../include

# Папка для сборки
BUILD_DIR = build

# Исходные файлы
SRC = src/array.cpp src/flist.cpp src/dlist.cpp src/stack.cpp src/queue.cpp src/hash_table.cpp src/avl_tree.cpp

# Файлы тестов
TEST_SRC = tests/test_array.cpp tests/test_flist.cpp tests/test_dlist.cpp tests/test_stack.cpp tests/test_queue.cpp tests/test_hash_table.cpp tests/test_avl_tree.cpp

# Библиотеки Google Test
GTEST_LIBS = -lgtest -lgtest_main -pthread

# Итоговые файлы
APP_TARGET = $(BUILD_DIR)/app
TEST_TARGET = $(BUILD_DIR)/run_tests

# Цель по умолчанию
all: $(APP_TARGET)

# Сборка основной программы
$(APP_TARGET): main.cpp $(SRC)
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CXX) $(CXXFLAGS) -o app ../main.cpp $(addprefix ../, $(SRC))

# Сборка тестов
$(TEST_TARGET): $(TEST_SRC) $(SRC)
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CXX) $(CXXFLAGS) --coverage -o run_tests $(addprefix ../, $(TEST_SRC) $(SRC)) $(GTEST_LIBS)

# Запуск тестов
test: $(TEST_TARGET)
	cd $(BUILD_DIR) && ./run_tests

# Генерация покрытия
coverage: test
	# 1. Собираем все данные покрытия
	cd $(BUILD_DIR) && lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch,mismatch
	# 2. Удаляем из отчета системные пути (/usr/) и папку с тестами, чтобы считалось покрытие только твоего кода в src/ и include/
	cd $(BUILD_DIR) && lcov --remove coverage.info '/usr/*' '*/tests/*' --output-file coverage.info --ignore-errors unused
	# 3. Генерируем HTML
	cd $(BUILD_DIR) && genhtml coverage.info --output-directory coverage_report
	@echo "HTML отчет готов: $(BUILD_DIR)/coverage_report/index.html"
	
# Линтер
lint:
	@echo "Запуск линтера cppcheck..."
	cppcheck --enable=all --suppress=missingIncludeSystem -Iinclude main.cpp src/
	@echo "Проверка завершена."


# Сборка бенчмарка (добавляем флаг -O2 для максимальной оптимизации, чтобы замеры были честными)
$(BUILD_DIR)/benchmark: benchmark.cpp $(SRC)
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CXX) $(CXXFLAGS) -O2 -o benchmark ../benchmark.cpp $(addprefix ../, $(SRC))

# Запуск бенчмарка
bench: $(BUILD_DIR)/benchmark
	cd $(BUILD_DIR) && ./benchmark

	
# Очистка
clean:
	rm -rf $(BUILD_DIR)