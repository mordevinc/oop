#ifndef DLIST_H
#define DLIST_H

#include <iostream>
#include <string>

// Класс двусвязного списка.
class DoublyList {
private:
    // Узел двусвязного списка.
    struct Node {
        std::string data;
        Node* prev; // Указатель на предыдущий узел
        Node* next; // Указатель на следующий узел
        explicit Node(const std::string& val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head; // Указатель на первый элемент (голова)
    Node* tail; // Указатель на последний элемент (хвост)
    size_t sz;  // Количество элементов

    // Вспомогательный поиск узла.
    Node* getNode(const std::string& target) const;

public:
    // Конструктор пустого списка.
    DoublyList();
    
    // Деструктор: удаляет все узлы.
    ~DoublyList();

    // Конструктор копирования (глубокая копия)
    DoublyList(const DoublyList& other);
    // Оператор присваивания (глубокая копия)
    DoublyList& operator=(const DoublyList& other);

    // Добавление элемента в начало списка.
    void push_front(const std::string& value);
    
    // Добавление элемента в конец списка.
    void push_back(const std::string& value);

    // Вставка элемента после узла с заданным значением.
    void insert_after(const std::string& target, const std::string& value);
    
    // Вставка элемента перед узлом с заданным значением.
    void insert_before(const std::string& target, const std::string& value);

    // Удаление первого элемента.
    void pop_front();
    
    // Удаление последнего элемента.
    void pop_back();
    
    // Удаление элемента после заданного.
    void remove_after(const std::string& target);
    
    // Удаление элемента перед заданным.
    void remove_before(const std::string& target);
    
    // Удаление по значению.
    void remove_by_value(const std::string& value);

    // Получение размера списка.
    size_t size() const;
    
    // Вывод списка в консоль.
    void print() const;
    
    // Вывод списка с конца (обратный порядок).
    void printReverse() const;

    // Сохранение списка в бинарный файл.
    void save(const std::string& filename) const;
    
    // Загрузка списка из бинарного файла.
    void load(const std::string& filename);
};

#endif