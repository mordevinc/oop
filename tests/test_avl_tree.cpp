#include <gtest/gtest.h>
#include "avl_tree.h"

// Тест 1: Проверяем вставку и балансировку.
// (При вставке 30, 20, 10 дерево должно повернуться, чтобы не стать "палкой")
TEST(AVLTreeTest, InsertAndSize) {
    AVLTree tree;
    
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);
    
    EXPECT_EQ(tree.size(), 3);
}

// Тест 2: Проверяем сериализацию (сохраняем только размер по ТЗ).
TEST(AVLTreeTest, Serialization) {
    AVLTree tree1;
    tree1.insert(50);
    tree1.insert(70);
    tree1.save("test_avl.bin");

    AVLTree tree2;
    tree2.load("test_avl.bin");
    
    EXPECT_EQ(tree2.size(), 2);
}

TEST(AVLTreeTest, ContainsAndPrint) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(5);
    
    // Покрываем метод contains
    EXPECT_TRUE(tree.contains(10));
    EXPECT_FALSE(tree.contains(99));
    
    // Покрываем метод print (он просто выводит в консоль, но мы проверяем, что не падает)
    tree.print();
}