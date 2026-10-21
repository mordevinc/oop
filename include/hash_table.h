#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "flist.h"
#include <string>

// Класс хеш-таблицы (разрешение коллизий методом цепочек).
class HashTable {
private:
    ForwardList* buckets; // Массив списков (корзин)
    size_t capacity;      // Количество корзин
    size_t sz;            // Общее количество элементов

    // Внутренняя хеш-функция для вычисления индекса корзины.
    size_t hashFunc(const std::string& key) const;

public:
    // Конструктор. Выделяет память под массив корзин.
    explicit HashTable(size_t cap = 100);
    
    // Деструктор. Освобождает память.
    ~HashTable();

    // Геттер для получения количества элементов (нужен для тестов)
    size_t size() const; 

    // Конструктор копирования
    HashTable(const HashTable& other);
    // Оператор присваивания
    HashTable& operator=(const HashTable& other);

    // Добавление пары ключ-значение.
    void insert(const std::string& key, const std::string& value);
    
    // Вывод всей таблицы в консоль.
    void print() const;

    // Сохранение таблицы в файл.
    void save(const std::string& filename) const;
    
    // Загрузка таблицы из файла.
    void load(const std::string& filename);
};

#endif