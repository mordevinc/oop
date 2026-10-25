#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "flist.h"
#include <string>

// Класс хеш-таблицы (разрешение коллизий методом цепочек).
class HashTable {
private:
    ForwardList* buckets; // Массив списков (корзин)
    size_t capacity;      // Количество корзин
    size_t sz;            // Общее количество элементов в таблице

    // Внутренняя хеш-функция для вычисления индекса корзины по ключу.
    size_t hashFunc(const std::string& key) const;

public:
    // Конструктор. Выделяет память под массив корзин.
    explicit HashTable(size_t cap = 100);
    
    // Конструктор копирования (правило трех).
    HashTable(const HashTable& other);
    
    // Оператор присваивания (правило трех).
    HashTable& operator=(const HashTable& other);
    
    // Деструктор. Освобождает память.
    ~HashTable();

    // Добавление пары ключ-значение.
    void insert(const std::string& key, const std::string& value);
    
    // Получение значения по ключу (возвращает пустую строку, если нет).
    std::string get(const std::string& key) const;
    
    // Удаление по ключу.
    void remove(const std::string& key);
    
    // Получение текущего количества элементов.
    size_t size() const;

    // Вывод всей таблицы в консоль.
    void print() const;

    // Сохранение таблицы в файл.
    void save(const std::string& filename) const;
    
    // Загрузка таблицы из файла.
    void load(const std::string& filename);
};

#endif