#include <gtest/gtest.h>
#include "hash_table.h"

TEST(HashTableTest, InsertAndGet) {
    HashTable ht(10);
    ht.insert("name", "John");
    ht.insert("age", "25");
    
    EXPECT_EQ(ht.size(), 2);
    EXPECT_EQ(ht.get("name"), "John");
    EXPECT_EQ(ht.get("unknown"), ""); 
}

TEST(HashTableTest, UpdateAndRemove) {
    HashTable ht(10);
    ht.insert("key", "value1");
    ht.insert("key", "value2"); // Обновление
    EXPECT_EQ(ht.size(), 1);
    EXPECT_EQ(ht.get("key"), "value2");
    
    ht.remove("key");
    EXPECT_EQ(ht.size(), 0);
    
    // Удаление несуществующего ключа
    ht.remove("unknown"); 
    EXPECT_EQ(ht.size(), 0);
}

// Тест коллизий и копирования
TEST(HashTableTest, CollisionsAndCopy) {
    HashTable ht1(5); // Маленькая таблица для вызова коллизий
    ht1.insert("key1", "val1");
    ht1.insert("key2", "val2"); // Может попасть в ту же корзину
    
    ht1.print();
    
    // Проверка глубокого копирования
    HashTable ht2 = ht1;
    EXPECT_EQ(ht2.size(), 2);
    EXPECT_EQ(ht2.get("key1"), "val1");
    
    ht1.save("test_ht.bin");
    HashTable ht3(5);
    ht3.load("test_ht.bin");
    EXPECT_EQ(ht3.get("key1"), "val1");
}