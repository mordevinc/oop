#include <gtest/gtest.h>
#include "flist.h"

// Тест 1: Проверяем добавление элементов и поиск.
TEST(ForwardListTest, PushAndFind) {
    ForwardList list;
    
    // Добавляем в конец и в начало
    list.push_back("Middle");
    list.push_front("First");
    
    EXPECT_EQ(list.size(), 2);
    
    // Проверяем поиск существующего и несуществующего элемента
    EXPECT_TRUE(list.find("First"));
    EXPECT_FALSE(list.find("NotFound"));
}

// Тест 2: Проверяем сериализацию (сохранение/загрузка).
TEST(ForwardListTest, Serialization) {
    ForwardList list1;
    list1.push_back("Node1");
    list1.push_back("Node2");
    list1.save("test_flist.bin");

    ForwardList list2;
    list2.load("test_flist.bin");

    EXPECT_EQ(list2.size(), 2);
    EXPECT_TRUE(list2.find("Node1"));
}

// В ForwardListTest
TEST(ForwardListTest, PrintTest) {
    ForwardList list;
    list.push_back("A");
    list.print(); // Покрываем функцию print
}
