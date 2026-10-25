#include <gtest/gtest.h>
#include "flist.h"

// 1. Проверка pop_back для списка из нескольких элементов (закрывает цикл while в pop_back)
TEST(ForwardListTest, PushAndPopMultiElement) {
    ForwardList list;
    list.push_back("A");
    list.push_back("B");
    list.push_front("Z"); // Z -> A -> B
    
    // Удаляем с конца, когда элементов > 1
    list.pop_back(); // Z -> A
    EXPECT_EQ(list.size(), 2);
    
    // Удаляем с начала
    list.pop_front(); // A
    EXPECT_EQ(list.size(), 1);

    // Удаляем единственный элемент
    list.pop_back(); 
    EXPECT_EQ(list.size(), 0);
}

// 2. Вставка в середину (закрывает нормальную ветку insert_after и insert_before)
TEST(ForwardListTest, InsertMiddle) {
    ForwardList list;
    list.push_back("A");
    list.push_back("C"); // A -> C
    
    // Вставка после "A" (не хвоста)
    list.insert_after("A", "B"); // A -> B -> C
    
    // Вставка перед "C" (не головы)
    list.insert_before("C", "X"); // A -> B -> X -> C
    
    EXPECT_EQ(list.size(), 4);
    EXPECT_TRUE(list.find("B"));
    EXPECT_TRUE(list.find("X"));
    
    // Попытка вставки перед несуществующим (цикл доходит до nullptr)
    list.insert_before("Ghost", "Y");
    EXPECT_EQ(list.size(), 4);
}

// 3. Удаление из середины по значению, с конца и с середины через remove_after/remove_before
TEST(ForwardListTest, RemoveMiddleAndTails) {
    ForwardList list;
    list.push_back("A");
    list.push_back("B");
    list.push_back("C");
    list.push_back("D"); // A -> B -> C -> D
    
    // Удаление из середины по значению
    list.remove_by_value("B"); // A -> C -> D
    
    // Удаление хвоста по значению (закрывает ветку if (temp == tail))
    list.remove_by_value("D"); // A -> C
    
    // Удаление после середины (удаляем C)
    list.remove_after("A"); // A
    
    // Удаление перед хвостом (удаляем A, остается E)
    list.push_back("E"); // A -> E
    list.remove_before("E"); 
    
    EXPECT_EQ(list.size(), 1);
    EXPECT_TRUE(list.find("E"));
}

// 4. Удаление из середины по ключу (для HashTable)
TEST(ForwardListTest, RemoveMiddleByKey) {
    ForwardList list;
    list.push_back("k1:v1");
    list.push_back("k2:v2");
    list.push_back("k3:v3");
    
    // Удаляем из середины
    EXPECT_TRUE(list.removeByKey("k2")); 
    EXPECT_EQ(list.size(), 2);
    
    EXPECT_EQ(list.getValueByKey("k1"), "v1");
    EXPECT_EQ(list.getValueByKey("k3"), "v3");
    EXPECT_EQ(list.getValueByKey("k2"), ""); // Не найдено
}

// 5. Копирование, Самоприсваивание и Сериализация
TEST(ForwardListTest, CopySelfAssignmentAndSerialization) {
    ForwardList list1;
    list1.push_back("Data");
    list1.print();
    
    // Конструктор копирования
    ForwardList list2 = list1;
    
    // Оператор присваивания
    ForwardList list3;
    list3 = list1;
    
    // Самоприсваивание (закрывает ветку if (this != &other))
    list1 = list1;
    
    EXPECT_EQ(list1.size(), 1);
    EXPECT_EQ(list2.size(), 1);
    EXPECT_EQ(list3.size(), 1);
    
    // Сериализация
    list1.save("test_flist.bin");
    ForwardList list4;
    list4.load("test_flist.bin");
    EXPECT_EQ(list4.size(), 1);
    
    // Загрузка несуществующего файла
    ForwardList list5;
    list5.load("ghost.bin");
    EXPECT_EQ(list5.size(), 0);
}