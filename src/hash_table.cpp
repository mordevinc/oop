#include "hash_table.h"
#include <fstream>
#include <numeric> 

// Выделяем массив корзин (каждая корзина - это односвязный список).
HashTable::HashTable(size_t cap) : capacity(cap), sz(0) {
    buckets = new ForwardList[capacity];
}

// Освобождаем массив корзин.
HashTable::~HashTable() {
    delete[] buckets;
}

// Возвращает текущее количество элементов в таблице
size_t HashTable::size() const {
    return sz;
}

// Конструктор копирования (глубокая копия)
HashTable::HashTable(const HashTable& other) : capacity(other.capacity), sz(other.sz) {
    buckets = new ForwardList[capacity];
    for (size_t i = 0; i < capacity; ++i) {
        buckets[i] = other.buckets[i];
    }
}

// Оператор присваивания
HashTable& HashTable::operator=(const HashTable& other) {
    if (this != &other) {
        delete[] buckets;
        capacity = other.capacity;
        sz = other.sz;
        buckets = new ForwardList[capacity];
        for (size_t i = 0; i < capacity; ++i) {
            buckets[i] = other.buckets[i];
        }
    }
    return *this;
}


// Хеш-функция: складываем ASCII-коды символов и берем остаток от деления на вместимость.
size_t HashTable::hashFunc(const std::string& key) const {
    // Используем std::accumulate вместо ручного цикла
    size_t sum = std::accumulate(key.begin(), key.end(), 0);
    return sum % capacity;
}

// Вставка: склеиваем ключ и значение через двоеточие и пихаем в список.
void HashTable::insert(const std::string& key, const std::string& value) {
    size_t idx = hashFunc(key); // Вычисляем индекс корзины
    buckets[idx].push_back(key + ":" + value); // Кладем в конец списка
    sz++;
}

// Печать таблицы. Идем по всем корзинам, если корзина не пуста - печатаем её.
void HashTable::print() const {
    for (size_t i = 0; i < capacity; ++i) {
        if (buckets[i].size() > 0) {
            std::cout << "[" << i << "]: ";
            buckets[i].print();
        }
    }
}

// Сохранение. Сохраняем общий размер и каждый бакет в отдельный файл.
void HashTable::save(const std::string& filename) const {
    std::ofstream f(filename, std::ios::binary);
    f.write(reinterpret_cast<const char*>(&sz), sizeof(sz));
    
    for (size_t i = 0; i < capacity; ++i) {
        std::string bucketFile = filename + "_b" + std::to_string(i);
        buckets[i].save(bucketFile);
    }
}

// Загрузка. Читаем размер и восстанавливаем каждый бакет.
void HashTable::load(const std::string& filename) {
    std::ifstream f(filename, std::ios::binary);
    if (!f) return;
    f.read(reinterpret_cast<char*>(&sz), sizeof(sz));
    
    for (size_t i = 0; i < capacity; ++i) {
        std::string bucketFile = filename + "_b" + std::to_string(i);
        buckets[i].load(bucketFile);
    }
}