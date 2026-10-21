#ifndef DLIST_H
#define DLIST_H

#include <iostream>
#include <string>

// Класс двусвязного списка.
class DoublyList {
private:
    // Узел двусвязного списка.
    struct Node {
        std::string data; // Данные
        Node* prev;       // Указатель на предыдущий узел
        Node* next;       // Указатель на следующий узел
        explicit Node(const std::string& val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head; // Указатель на первый элемент (голова)
    Node* tail; // Указатель на последний элемент (хвост)
    size_t sz;  // Количество элементов

public:
    // Конструктор пустого списка.
    DoublyList();
    
    // Деструктор: удаляет все узлы.
    ~DoublyList();

    // Добавление элемента в конец списка.
    void push_back(const std::string& value);
    
    // Добавление элемента в начало списка.
    void push_front(const std::string& value);
    
    // Получение размера списка.
    size_t size() const;
    
    // Вывод списка в консоль.
    void print() const;

    // Сохранение списка в бинарный файл.
    void save(const std::string& filename) const;
    
    // Загрузка списка из бинарного файла.
    void load(const std::string& filename);
};

#endif