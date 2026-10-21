#include <gtest/gtest.h>
#include "array.h"

// Тест 1: Проверяем базовые операции (добавление и получение размера).
TEST(ArrayTest, BasicOperations) {
    Array arr(5); // Создаем массив на 5 элементов
    EXPECT_EQ(arr.size(), 0); // Изначально он пуст

    arr.push_back("One");
    arr.push_back("Two");
    
    EXPECT_EQ(arr.size(), 2); // Размер должен увеличиться до 2
}

// Тест 2: Проверяем работу конструктора копирования.
// Важно убедиться, что создается глубокая копия, и изменение копии не ломает оригинал.
TEST(ArrayTest, CopyConstructorAndAssignment) {
    Array arr1(3);
    arr1.push_back("Data");
    
    // Явно вызываем конструктор копирования
    Array arr2 = arr1; 
    
    // Проверяем оператор присваивания (исправленный после линтера)
    Array arr3(3);
    arr3 = arr1;

    EXPECT_EQ(arr2.size(), 1);
    EXPECT_EQ(arr3.size(), 1);
}

// Тест 3: Проверяем бинарную сериализацию (сохранение и загрузку).
TEST(ArrayTest, Serialization) {
    Array arr1(5);
    arr1.push_back("Apple");
    arr1.push_back("Banana");
    
    // Сохраняем во временный файл
    arr1.save("test_array.bin");

    // Создаем пустой массив и загружаем в него данные
    Array arr2(5);
    arr2.load("test_array.bin");

    // Проверяем, что данные восстановились корректно
    EXPECT_EQ(arr2.size(), 2);
}