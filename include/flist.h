#ifndef FLIST_H
#define FLIST_H

#include <iostream>
#include <string>

// Класс односвязного списка.
class ForwardList {
private:
    // Внутренняя структура узла.
    struct Node {
        std::string data;
        Node* next; // Указатель на следующий узел
        explicit Node(const std::string& val) : data(val), next(nullptr) {}
    };

    Node* head;  // Указатель на первый элемент списка
    Node* tail;  // Указатель на последний элемент списка
    size_t sz;   // Количество элементов в списке

    // Вспомогательный метод для поиска узла (скрыт от пользователя).
    Node* getNode(const std::string& target) const;

public:
    // Конструктор: создает пустой список.
    ForwardList();
    
    // Деструктор: удаляет все узлы, чтобы не было утечек памяти.
    ~ForwardList();

    // Конструктор копирования (глубокая копия)
    ForwardList(const ForwardList& other);
    // Оператор присваивания (глубокая копия)
    ForwardList& operator=(const ForwardList& other);

    // Добавление элемента в начало списка.
    void push_front(const std::string& value);
    
    // Добавление элемента в конец списка.
    void push_back(const std::string& value);

    // Вставка элемента после узла с заданным значением.
    void insert_after(const std::string& target, const std::string& value);
    
    // Вставка элемента перед узлом с заданным значением.
    void insert_before(const std::string& target, const std::string& value);

    // Удаление первого элемента (головы).
    void pop_front();
    
    // Удаление последнего элемента (хвоста).
    void pop_back();
    
    // Удаление элемента, стоящего после заданного.
    void remove_after(const std::string& target);
    
    // Удаление элемента, стоящего перед заданным.
    void remove_before(const std::string& target);
    
    // Удаление первого найденного элемента с заданным значением.
    void remove_by_value(const std::string& value);

    // Найти значение по ключу (ищет строку, начинающуюся с "key:")
    std::string getValueByKey(const std::string& key) const;
    // Удалить элемент по ключу
    bool removeByKey(const std::string& key);

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