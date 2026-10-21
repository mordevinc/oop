#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>

// Класс очереди (FIFO - First In, First Out).
class Queue {
private:
    // Узел очереди.
    struct Node {
        std::string data;
        Node* next;
        explicit Node(const std::string& val) : data(val), next(nullptr) {}
    };

    Node* head; // Начало очереди (откуда забираем)
    Node* tail; // Конец очереди (куда кладем)
    size_t sz;  // Количество элементов

public:
    // Конструктор.
    explicit Queue(size_t cap = 100);
    
    // Деструктор.
    ~Queue();

    // Добавить элемент в конец очереди.
    void push(const std::string& value);
    
    // Забрать элемент из начала очереди.
    std::string pop();
    
    // Проверка на пустоту.
    bool empty() const;
    
    // Получить размер.
    size_t size() const;
    
    // Вывести очередь в консоль.
    void print() const;

    // Сохранить очередь в файл.
    void save(const std::string& filename) const;
    
    // Загрузить очередь из файла.
    void load(const std::string& filename);
};

#endif