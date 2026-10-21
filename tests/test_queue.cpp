#include <gtest/gtest.h>
#include "queue.h"

// Тест 1: Проверяем принцип FIFO (первый пришел, первый вышел).
TEST(QueueTest, PushPopFIFO) {
    Queue queue;
    EXPECT_TRUE(queue.empty());

    queue.push("First");
    queue.push("Second");
    
    EXPECT_EQ(queue.size(), 2);

    // Забираем элементы (должны идти в том же порядке, в котором добавляли)
    EXPECT_EQ(queue.pop(), "First");
    EXPECT_EQ(queue.pop(), "Second");
    EXPECT_TRUE(queue.empty());
}

// Тест 2: Проверяем сериализацию.
TEST(QueueTest, Serialization) {
    Queue queue1;
    queue1.push("Task1");
    queue1.push("Task2");
    queue1.save("test_queue.bin");

    Queue queue2;
    queue2.load("test_queue.bin");

    EXPECT_EQ(queue2.size(), 2);
    EXPECT_EQ(queue2.pop(), "Task1"); // Первый элемент должен быть на месте
}