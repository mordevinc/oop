#include <gtest/gtest.h>
#include "stack.h"

// Тест 1: Проверяем базовый принцип LIFO (последний пришел, первый вышел).
TEST(StackTest, PushPopLIFO) {
    Stack stack;
    EXPECT_TRUE(stack.empty()); // Стек изначально пуст

    stack.push("First");
    stack.push("Second"); // Этот элемент на вершине
    
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 2);

    // Забираем элементы (должны идти в обратном порядке)
    EXPECT_EQ(stack.pop(), "Second");
    EXPECT_EQ(stack.pop(), "First");
    EXPECT_TRUE(stack.empty());
}

// Тест 2: Проверяем сериализацию.
TEST(StackTest, Serialization) {
    Stack stack1;
    stack1.push("Bottom");
    stack1.push("Top");
    stack1.save("test_stack.bin");

    Stack stack2;
    stack2.load("test_stack.bin");

    EXPECT_EQ(stack2.size(), 2);
    EXPECT_EQ(stack2.pop(), "Top"); // Проверяем, что порядок сохранился
}

// В StackTest
TEST(StackTest, PrintTest) {
    Stack s;
    s.push("X");
    s.print();
}