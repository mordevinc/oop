#include "dlist.h"
#include <fstream>

// Инициализация пустого списка.
DoublyList::DoublyList() : head(nullptr), tail(nullptr), sz(0) {}

// Деструктор. Удаляем все узлы.
DoublyList::~DoublyList() {
    Node* curr = head;
    while (curr != nullptr) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

// Добавление в конец.
void DoublyList::push_back(const std::string& value) {
    Node* newNode = new Node(value);
    newNode->prev = tail; // Новый узел назад ссылается на старый хвост
    
    if (tail != nullptr) {
        tail->next = newNode; // Старый хвост вперед ссылается на новый узел
    }
    tail = newNode; // Новый узел становится хвостом
    
    if (head == nullptr) { // Если список был пуст
        head = newNode;
    }
    sz++;
}

// Добавление в начало.
void DoublyList::push_front(const std::string& value) {
    Node* newNode = new Node(value);
    newNode->next = head; // Новый узел вперед ссылается на старую голову
    
    if (head != nullptr) {
        head->prev = newNode; // Старая голова назад ссылается на новый узел
    }
    head = newNode;
    
    if (tail == nullptr) { // Если список был пуст
        tail = newNode;
    }
    sz++;
}

// Возврат размера.
size_t DoublyList::size() const { 
    return sz; 
}

// Вывод списка.
void DoublyList::print() const {
    Node* curr = head;
    std::cout << "List: ";
    while (curr != nullptr) {
        std::cout << curr->data << " <-> ";
        curr = curr->next;
    }
    std::cout << "nullptr\n";
}

// Сохранение. Логика абсолютно такая же, как у односвязного.
void DoublyList::save(const std::string& filename) const {
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

// Загрузка.
void DoublyList::load(const std::string& filename) {
    std::ifstream f(filename, std::ios::binary);
    if (!f) return;
    
    // Очистка памяти перед загрузкой
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
        
        push_back(temp);
    }
}