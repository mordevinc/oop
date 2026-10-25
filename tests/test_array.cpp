#include <gtest/gtest.h>
#include "array.h"

// Тест 1: Проверяем базовое добавление элементов и получение размера.
TEST(ArrayTest, BasicOperations) {
    Array arr(5); // Создаем массив на 5 элементов
    arr.push_back("One");
    arr.push_back("Two");
    
    // Ожидаем, что после добавления двух элементов размер станет 2
    EXPECT_EQ(arr.size(), 2);
}

// Тест 2: Проверяем работу конструктора копирования и оператора присваивания.
// Это важно для правила трех, чтобы избежать двойного удаления памяти.
TEST(ArrayTest, CopyConstructorAndAssignment) {
    Array arr1(3);
    arr1.push_back("Data");
    
    // Явно вызываем конструктор копирования
    Array arr2 = arr1; 
    
    // Вызываем оператор присваивания
    Array arr3(3);
    arr3 = arr1;
    
    EXPECT_EQ(arr2.size(), 1);
    EXPECT_EQ(arr3.size(), 1);
}

// Тест 3: Проверяем дополнительные методы (вставка, замена, удаление по индексу).
// Эти тесты нужны, чтобы линтер не ругался на "unusedFunction".
TEST(ArrayTest, NewMethods) {
    Array arr(5);
    arr.push_back("A");
    arr.push_back("C");
    
    // Проверяем вставку по индексу (должно сдвинуть "C" вправо)
    arr.insert_at(1, "B");
    EXPECT_EQ(arr.get(1), "B");
    
    // Проверяем замену элемента по индексу
    arr.set(1, "X");
    EXPECT_EQ(arr.get(1), "X");
    
    // Проверяем удаление по индексу (должно сдвинуть элементы влево)
    arr.remove_at(1);
    EXPECT_EQ(arr.get(1), "C"); // На месте "X" теперь "C"
    EXPECT_EQ(arr.size(), 2);
}

// Тест 4: Проверяем бинарную сериализацию (сохранение и загрузку).
TEST(ArrayTest, Serialization) {
    Array arr1(5);
    arr1.push_back("Apple");
    
    // Сохраняем во временный файл
    arr1.save("test_array.bin");
    
    // Создаем пустой массив и загружаем в него данные
    Array arr2(5);
    arr2.load("test_array.bin");
    
    // Проверяем, что данные восстановились
    EXPECT_EQ(arr2.size(), 1);
}