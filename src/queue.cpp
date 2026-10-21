#include "queue.h"
#include <fstream>

// Инициализация пустой очереди.
// Параметр cap оставлен для совместимости.
Queue::Queue(size_t cap) : head(nullptr), tail(nullptr), sz(0) {
    (void)cap; // Явно указываем компилятору, что параметр не используется
}

// Деструктор.
Queue::~Queue() {
    while (head != nullptr) { 
        Node* t = head; 
        head = head->next; 
        delete t; 
    }
}

// Добавление в конец (в хвост).
void Queue::push(const std::string& value) {
    Node* newNode = new Node(value);
    if (tail == nullptr) { // Если очередь была пуста
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode; // Старый хвост ссылается на новый узел
        tail = newNode;       // Новый узел становится хвостом
    }
    sz++;
}

// Извлечение из начала (из головы).
std::string Queue::pop() {
    if (head == nullptr) return "";
    
    Node* temp = head;
    std::string val = temp->data;
    head = head->next; // Сдвигаем голову вперед
    
    if (head == nullptr) { // Если очередь опустела, хвост тоже обнуляем
        tail = nullptr; 
    }
    
    delete temp;
    sz--;
    return val;
}

// Проверка на пустоту.
bool Queue::empty() const { 
    return head == nullptr; 
}

// Размер.
size_t Queue::size() const { 
    return sz; 
}

// Печать очереди (от начала к концу).
void Queue::print() const {
    Node* curr = head;
    std::cout << "Queue: ";
    while (curr != nullptr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << "\n";
}

// Сохранение.
void Queue::save(const std::string& filename) const {
    std::ofstream f(filename, std::ios::binary);
    f.write(reinterpret_cast<const char*>(&sz), sizeof(sz));
    Node* curr = head;
    while (curr != nullptr) {
        size_t len = curr->data.size();
        f.write(reinterpret_cast<const char*>(&len), sizeof(len));
        f.write(curr->data.c_str(), len);
        curr = curr->next;
    }
}

// Загрузка. Восстанавливаем элементы через push (добавляя в конец).
void Queue::load(const std::string& filename) {
    std::ifstream f(filename, std::ios::binary);
    if (!f) return;
    
    // Очистка
    while (head != nullptr) { 
        Node* t = head; 
        head = head->next; 
        delete t; 
    }
    tail = nullptr; 
    sz = 0;
    
    size_t file_sz = 0;
    if (!f.read(reinterpret_cast<char*>(&file_sz), sizeof(file_sz))) return;
    
    for (size_t i = 0; i < file_sz; ++i) {
        size_t len = 0;
        if (!f.read(reinterpret_cast<char*>(&len), sizeof(len))) break;
        
        std::string temp(len, '\0');
        if (!f.read(&temp[0], len)) break;
        
        push(temp);
    }
}