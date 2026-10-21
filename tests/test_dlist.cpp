#include <gtest/gtest.h>
#include "dlist.h"

// Тест 1: Проверяем добавление с двух сторон.
TEST(DoublyListTest, PushOperations) {
    DoublyList list;
    
    list.push_back("Back");
    list.push_front("Front");
    
    EXPECT_EQ(list.size(), 2);
}

// Тест 2: Проверяем сохранение и загрузку.
TEST(DoublyListTest, Serialization) {
    DoublyList list1;
    list1.push_back("A");
    list1.push_back("B");
    list1.save("test_dlist.bin");

    DoublyList list2;
    list2.load("test_dlist.bin");

    EXPECT_EQ(list2.size(), 2);
}

// В DoublyListTest
TEST(DoublyListTest, PrintTest) {
    DoublyList list;
    list.push_back("B");
    list.print();
}