#include <gtest/gtest.h>
#include "hash_table.h"

// Тест 1: Проверяем базовую вставку.
TEST(HashTableTest, InsertOperations) {
    HashTable ht(10); // 10 корзин
    
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");
    
    // Размер таблицы должен вырасти
    EXPECT_EQ(ht.size(), 2);
}

// Тест 2: Проверяем правило трех (копирование) и сериализацию.
TEST(HashTableTest, CopyAndSerialization) {
    HashTable ht1(5);
    ht1.insert("A", "1");
    
    // Копируем таблицу (используется конструктор копирования)
    HashTable ht2 = ht1;
    EXPECT_EQ(ht2.size(), 1);
    
    // Проверяем сохранение/загрузку
    ht1.save("test_ht.bin");
    HashTable ht3(5);
    ht3.load("test_ht.bin");
    EXPECT_EQ(ht3.size(), 1);
}

TEST(HashTableTest, PrintTest) {
    HashTable ht(5);
    ht.insert("k", "v");
    ht.print(); // Покрываем print
}