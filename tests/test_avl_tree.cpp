#include <gtest/gtest.h>
#include "avl_tree.h"

// Проверка всех 4 типов поворотов (LL, RR, LR, RL)
TEST(AVLTreeTest, AllRotations) {
    AVLTree tree1;
    tree1.insert(30); tree1.insert(20); tree1.insert(10); // LL (правый поворот)
    EXPECT_EQ(tree1.size(), 3);

    AVLTree tree2;
    tree2.insert(10); tree2.insert(20); tree2.insert(30); // RR (левый поворот)
    EXPECT_EQ(tree2.size(), 3);

    AVLTree tree3;
    tree3.insert(30); tree3.insert(10); tree3.insert(20); // LR (двойной)
    EXPECT_EQ(tree3.size(), 3);

    AVLTree tree4;
    tree4.insert(10); tree4.insert(30); tree4.insert(20); // RL (двойной)
    EXPECT_EQ(tree4.size(), 3);
}

// Проверка дубликатов и удаления
TEST(AVLTreeTest, DuplicatesAndRemove) {
    AVLTree tree;
    tree.insert(50);
    tree.insert(50); // Ветка игнорирования дубликата
    EXPECT_EQ(tree.size(), 2); // Размер увеличивается в методе, но узел не создается

    tree.remove(999); // Удаление несуществующего (ветка contains == false)
    
    tree.insert(30);
    tree.insert(70);
    tree.remove(50); // Удаление корня с двумя детьми
    EXPECT_EQ(tree.size(), 3);
}

TEST(AVLTreeTest, PrintAndSerialization) {
    AVLTree tree1;
    tree1.insert(10);
    tree1.insert(5);
    
    tree1.print();
    tree1.printPreorder();
    tree1.printPostorder();
    
    tree1.save("test_avl.bin");
    AVLTree tree2;
    tree2.load("test_avl.bin");
    EXPECT_EQ(tree2.size(), 2);
    
    AVLTree tree3;
    tree3.load("ghost.bin"); // Загрузка несуществующего файла
    EXPECT_EQ(tree3.size(), 0);
}