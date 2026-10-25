#include <gtest/gtest.h>
#include "dlist.h"

TEST(DoublyListTest, PushAndPopCoverage) {
    DoublyList list;
    list.push_back("A");
    list.push_back("B");
    list.push_front("Z"); // Z <-> A <-> B
    
    // pop_back из многоэлементного
    list.pop_back(); // Z <-> A
    // pop_front из многоэлементного
    list.pop_front(); // A
    // pop_back из одноэлементного
    list.pop_back(); // empty
    EXPECT_EQ(list.size(), 0);
    
    // Из пустого
    list.pop_back();
    list.pop_front();
}

TEST(DoublyListTest, InsertAndRemoveMiddle) {
    DoublyList list;
    list.push_back("A");
    list.push_back("C"); // A <-> C
    
    list.insert_after("A", "B"); // A <-> B <-> C
    list.insert_before("C", "X"); // A <-> B <-> X <-> C
    EXPECT_EQ(list.size(), 4);
    
    // Удаление по значению (из середины, хвоста, головы)
    list.remove_by_value("B"); // A <-> X <-> C
    list.remove_by_value("C"); // A <-> X
    list.remove_by_value("A"); // X
    
    list.remove_after("X"); // нет следующего
    list.remove_before("X"); // нет предыдущего
    EXPECT_EQ(list.size(), 1);
}

TEST(DoublyListTest, CopyAndSelfAssignment) {
    DoublyList list1;
    list1.push_back("Data");
    
    DoublyList list2 = list1; // Копирование
    DoublyList list3;
    list3 = list1; // Присваивание
    list1 = list1; // Самоприсваивание
    
    list1.print();
    list1.printReverse();
    
    list1.save("test_dlist.bin");
    DoublyList list4;
    list4.load("test_dlist.bin");
    EXPECT_EQ(list4.size(), 1);
    
    DoublyList list5;
    list5.load("ghost.bin");
}