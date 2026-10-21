#include "array.h"
#include <fstream>

// Конструктор. Выделяем память в куче (new) под массив строк.
Array::Array(size_t cap) : data(new std::string[cap]), sz(0), capacity(cap) {}

// Конструктор копирования (необходим по правилу трех, чтобы избежать двойного удаления).
Array::Array(const Array& other) : data(new std::string[other.capacity]), sz(other.sz), capacity(other.capacity) {
    for (size_t i = 0; i < sz; ++i) {
        data[i] = other.data[i];
    }
}

// Оператор присваивания (исправление noOperatorEq).
// Сначала проверяем на самоприсваивание, затем очищаем старую память и копируем новую.
Array& Array::operator=(const Array& other) {
    if (this != &other) { // Защита от a = a
        delete[] data;    // Удаляем старые данные
        
        sz = other.sz;
        capacity = other.capacity;
        data = new std::string[capacity]; // Выделяем новую память
        
        for (size_t i = 0; i < sz; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

// Деструктор. Освобождаем память, чтобы не было утечек.
Array::~Array() {
    delete[] data;
}

// Добавление элемента в конец.
void Array::push_back(const std::string& value) {
    if (sz < capacity) {
        data[sz] = value;
        sz++;
    }
}

// Возвращает текущий размер (const означает, что метод не меняет объект).
size_t Array::size() const { 
    return sz; 
}

// Печать массива. Проходим циклом от 0 до sz и выводим каждый элемент.
void Array::print() const {
    std::cout << "[ ";
    for (size_t i = 0; i < sz; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << "]\n";
}

// Бинарная сериализация.
void Array::save(const std::string& filename) const {
    std::ofstream f(filename, std::ios::binary); 
    f.write(reinterpret_cast<const char*>(&sz), sizeof(sz));
    
    for (size_t i = 0; i < sz; ++i) {
        size_t len = data[i].size();
        f.write(reinterpret_cast<const char*>(&len), sizeof(len));
        f.write(data[i].c_str(), len);
    }
}

// Десериализация.
// Десериализация.
void Array::load(const std::string& filename) {
    std::ifstream f(filename, std::ios::binary);
    if (!f) return;
    
    size_t file_sz = 0;
    // Проверяем, удалось ли прочитать размер
    if (!f.read(reinterpret_cast<char*>(&file_sz), sizeof(file_sz))) return;
    
    // Ограничиваем размер вместимостью нашего массива
    sz = (file_sz < capacity) ? file_sz : capacity;
    
    for (size_t i = 0; i < sz; ++i) {
        size_t len = 0; // Обязательно инициализируем нулем
        if (!f.read(reinterpret_cast<char*>(&len), sizeof(len))) break; // Если не прочиталось - выходим
        
        std::string temp(len, '\0');
        if (!f.read(&temp[0], len)) break; // Если строку не прочитали - выходим
        
        data[i] = temp;
    }
}