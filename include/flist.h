#ifndef FLIST_H
#define FLIST_H

#include <iostream>
#include <string>

// Класс односвязного списка.
class ForwardList {
private:
    // Внутренняя структура узла (скрыта от пользователя).
    struct Node {
        std::string data; // Данные, хранящиеся в узле
        Node* next;       // Указатель на следующий узел
        explicit Node(const std::string& val) : data(val), next(nullptr) {}
    };

    Node* head;  // Указатель на первый элемент списка (голова)
    Node* tail;  // Указатель на последний элемент списка (хвост)
    size_t sz;   // Количество элементов в списке

public:
    // Конструктор: создает пустой список.
    ForwardList();
    
    // Деструктор: удаляет все узлы, чтобы не было утечек памяти.
    ~ForwardList();

    // Конструктор копирования (глубокая копия)
    ForwardList(const ForwardList& other);
    // Оператор присваивания (глубокая копия)
    ForwardList& operator=(const ForwardList& other);

    // Добавление элемента в конец списка.
    void push_back(const std::string& value);
    
    // Добавление элемента в начало списка.
    void push_front(const std::string& value);
    
    // Поиск элемента по значению (возвращает true, если найден).
    bool find(const std::string& value) const;
    
    // Возвращает количество элементов в списке.
    size_t size() const;
    
    // Вывод всего списка в консоль.
    void print() const;

    // Сохранение списка в бинарный файл.
    void save(const std::string& filename) const;
    
    // Загрузка списка из бинарного файла.
    void load(const std::string& filename);
};

#endif