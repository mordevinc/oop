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

void Array::load(const std::string& filename) {
    std::ifstream f(filename, std::ios::binary);
    if (!f) return;
    
    size_t file_sz = 0;
    if (!f.read(reinterpret_cast<char*>(&file_sz), sizeof(file_sz))) return; // Если файл пуст
    
    // Защита от мусора
    if (file_sz > 1000000) return;
    sz = (file_sz < capacity) ? file_sz : capacity;
    
    for (size_t i = 0; i < sz; ++i) {
        size_t len = 0;
        if (!f.read(reinterpret_cast<char*>(&len), sizeof(len))) break;
        if (len > 1000000) break; // Защита от чтения гигантской строки
        
        std::string temp(len, '\0');
        if (!f.read(&temp[0], len)) break;
        data[i] = temp;
    }
}

// Вставка по индексу (сдвигаем элементы вправо)
void Array::insert_at(size_t index, const std::string& value) {
    if (index > sz || sz >= capacity) return; // Проверка границ и наличия места
    // Идем с конца, освобождая место для нового элемента
    for (size_t i = sz; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    sz++;
}

// Получение по индексу
std::string Array::get(size_t index) const {
    if (index >= sz) return ""; // Если индекс вне границ, отдаем пустую строку
    return data[index];
}

// Замена по индексу
void Array::set(size_t index, const std::string& value) {
    if (index < sz) data[index] = value;
}

// Удаление по индексу (сдвигаем влево)
void Array::remove_at(size_t index) {
    if (index >= sz) return;
    for (size_t i = index; i < sz - 1; ++i) {
        data[i] = data[i + 1]; // Затираем удаляемый элемент следующим
    }
    sz--;
}