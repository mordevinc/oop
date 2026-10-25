#include "hash_table.h"
#include <fstream>
#include <numeric> // Нужно для std::accumulate (суммирование элементов)
#include <iostream>

// Выделяем массив корзин (каждая корзина - это односвязный список).
HashTable::HashTable(size_t cap) : capacity(cap), sz(0) {
    buckets = new ForwardList[capacity];
}

// Конструктор копирования (необходим по правилу трех).
// Выделяет новую память и копирует в нее все списки из другой таблицы.
HashTable::HashTable(const HashTable& other) : capacity(other.capacity), sz(other.sz) {
    buckets = new ForwardList[capacity];
    for (size_t i = 0; i < capacity; ++i) {
        buckets[i] = other.buckets[i]; // Использует оператор присваивания ForwardList
    }
}

// Оператор присваивания (правило трех). 
// Нужен, чтобы при `a = b` копировались данные, а не адреса памяти.
HashTable& HashTable::operator=(const HashTable& other) {
    if (this != &other) { // Защита от самоприсваивания (a = a)
        delete[] buckets; // Удаляем старую память
        
        capacity = other.capacity;
        sz = other.sz;
        buckets = new ForwardList[capacity]; // Выделяем новую память
        
        for (size_t i = 0; i < capacity; ++i) {
            buckets[i] = other.buckets[i];
        }
    }
    return *this;
}

// Освобождаем массив корзин.
HashTable::~HashTable() {
    delete[] buckets;
}

// Хеш-функция: складываем ASCII-коды символов и берем остаток от деления на вместимость.
size_t HashTable::hashFunc(const std::string& key) const {
    // Используем std::accumulate вместо ручного цикла (как советовал линтер)
    size_t sum = std::accumulate(key.begin(), key.end(), 0);
    return sum % capacity;
}

// Вставка: склеиваем ключ и значение через двоеточие и пихаем в нужный список.
// Добавление или обновление
void HashTable::insert(const std::string& key, const std::string& value) {
    size_t idx = hashFunc(key); // Вычисляем индекс корзины
    
    // Пытаемся удалить старый ключ (если он есть). 
    // Если removeByKey вернул false, значит ключа не было, и это новый элемент.
    bool existed = buckets[idx].removeByKey(key); 
    if (!existed) {
        sz++; // Увеличиваем размер таблицы только если ключ действительно новый
    }
    
    // Кладем в конец списка строку формата "key:value"
    buckets[idx].push_back(key + ":" + value);
}

// Получение значения по ключу.
std::string HashTable::get(const std::string& key) const {
    size_t idx = hashFunc(key); // Вычисляем индекс корзины
    // Просим список найти значение по ключу. Теперь idx используется!
    return buckets[idx].getValueByKey(key);
}

// Удаление по ключу.
void HashTable::remove(const std::string& key) {
    size_t idx = hashFunc(key); // Вычисляем индекс корзины
    
    // Пытаемся удалить из списка. Если удалилось — уменьшаем размер таблицы.
    if (buckets[idx].removeByKey(key)) {
        sz--;
    }
}

// Возвращает текущее количество элементов в таблице.
size_t HashTable::size() const {
    return sz;
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
        // Формируем имя файла для каждой корзины (например, "data.bin_b0")
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