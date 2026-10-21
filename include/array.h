#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <string>

// Класс динамического массива строк.
class Array {
private:
    std::string* data; // Указатель на массив в куче
    size_t sz;         // Текущее количество элементов
    size_t capacity;   // Максимальная вместимость

public:
    // Конструктор: выделяет память под массив заданной вместимости
    explicit Array(size_t cap);
    
    // Конструктор копирования: делает глубокую копию
    Array(const Array& other);
    
    // ДЕСТРУКТОР (нужен для очистки памяти)
    ~Array();

    // ОПЕРАТОР ПРИСВАИВАНИЯ (добавлен по требованию линтера noOperatorEq)
    // Нужен, чтобы при `a = b` копировались данные, а не адреса памяти.
    Array& operator=(const Array& other);

    // Добавляет элемент в конец
    void push_back(const std::string& value);
    
    // Возвращает текущее количество элементов
    size_t size() const;
    
    // Выводит все элементы в консоль
    void print() const;

    // Сохраняет массив в бинарный файл
    void save(const std::string& filename) const;
    
    // Загружает массив из бинарного файла
    void load(const std::string& filename);
};

#endif