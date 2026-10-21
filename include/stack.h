#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>

// Класс стека (LIFO - Last In, First Out).
class Stack {
private:
    // Узел стека.
    struct Node {
        std::string data;
        Node* next;
        explicit Node(const std::string& val) : data(val), next(nullptr) {}
    };
    
    Node* head; // Вершина стека (голова списка)
    size_t sz;  // Количество элементов

public:
    // Конструктор. Параметр cap оставлен для совместимости с заданием.
    explicit Stack(size_t cap = 100);
    
    // Деструктор: очищает память.
    ~Stack();

    // Положить элемент на вершину стека.
    void push(const std::string& value);
    
    // Снять элемент с вершины стека.
    std::string pop();
    
    // Проверить, пуст ли стек.
    bool empty() const;
    
    // Получить количество элементов.
    size_t size() const;
    
    // Вывести стек в консоль.
    void print() const;

    // Сохранить стек в файл.
    void save(const std::string& filename) const;
    
    // Загрузить стек из файла.
    void load(const std::string& filename);
};

#endif