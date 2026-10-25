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

// Конструктор копирования (по правилу трех)
DoublyList::DoublyList(const DoublyList& other) : head(nullptr), tail(nullptr), sz(0) {
    Node* curr = other.head;
    while (curr != nullptr) {
        push_back(curr->data); // Поэлементно копируем данные
        curr = curr->next;
    }
}

// Оператор присваивания (по правилу трех)
DoublyList& DoublyList::operator=(const DoublyList& other) {
    if (this != &other) { // Защита от самоприсваивания
        // Очищаем текущий список
        while (head != nullptr) {
            Node* t = head; 
            head = head->next; 
            delete t;
        }
        tail = nullptr; 
        sz = 0;
        
        // Копируем данные из другого списка
        Node* curr = other.head;
        while (curr != nullptr) {
            push_back(curr->data);
            curr = curr->next;
        }
    }
    return *this;
}

// Вспомогательный поиск узла.
DoublyList::Node* DoublyList::getNode(const std::string& target) const {
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data == target) return curr;
        curr = curr->next;
    }
    return nullptr;
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

// Вставка после заданного.
void DoublyList::insert_after(const std::string& target, const std::string& value) {
    Node* targetNode = getNode(target);
    if (targetNode == nullptr) return;
    
    if (targetNode == tail) { // Если после хвоста, это push_back
        push_back(value);
        return;
    }
    
    Node* newNode = new Node(value);
    newNode->prev = targetNode;
    newNode->next = targetNode->next;
    targetNode->next->prev = newNode;
    targetNode->next = newNode;
    sz++;
}

// Вставка перед заданным.
void DoublyList::insert_before(const std::string& target, const std::string& value) {
    Node* targetNode = getNode(target);
    if (targetNode == nullptr) return;
    
    if (targetNode == head) { // Если перед головой, это push_front
        push_front(value);
        return;
    }
    
    Node* newNode = new Node(value);
    newNode->next = targetNode;
    newNode->prev = targetNode->prev;
    targetNode->prev->next = newNode;
    targetNode->prev = newNode;
    sz++;
}

// Удаление из начала.
void DoublyList::pop_front() {
    if (head == nullptr) return;
    Node* temp = head;
    head = head->next;
    if (head != nullptr) head->prev = nullptr;
    else tail = nullptr;
    delete temp;
    sz--;
}

// Удаление с конца.
void DoublyList::pop_back() {
    if (tail == nullptr) return;
    Node* temp = tail;
    tail = tail->prev;
    if (tail != nullptr) tail->next = nullptr;
    else head = nullptr;
    delete temp;
    sz--;
}

// Удаление после заданного.
void DoublyList::remove_after(const std::string& target) {
    Node* targetNode = getNode(target);
    if (targetNode == nullptr || targetNode->next == nullptr) return;
    
    Node* temp = targetNode->next;
    targetNode->next = temp->next;
    if (temp->next != nullptr) temp->next->prev = targetNode;
    else tail = targetNode; // Если удалили хвост
    delete temp;
    sz--;
}

// Удаление перед заданным.
void DoublyList::remove_before(const std::string& target) {
    Node* targetNode = getNode(target);
    if (targetNode == nullptr || targetNode->prev == nullptr) return;
    
    Node* temp = targetNode->prev;
    targetNode->prev = temp->prev;
    if (temp->prev != nullptr) temp->prev->next = targetNode;
    else head = targetNode; // Если удалили голову
    delete temp;
    sz--;
}

// Удаление по значению.
void DoublyList::remove_by_value(const std::string& value) {
    Node* targetNode = getNode(value);
    if (targetNode == nullptr) return;
    
    if (targetNode == head) { pop_front(); return; }
    if (targetNode == tail) { pop_back(); return; }
    
    targetNode->prev->next = targetNode->next;
    targetNode->next->prev = targetNode->prev;
    delete targetNode;
    sz--;
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

// Обратный вывод.
void DoublyList::printReverse() const {
    Node* curr = tail;
    std::cout << "Reverse: ";
    while (curr != nullptr) {
        std::cout << curr->data << " <-> ";
        curr = curr->prev;
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
    
    while (head != nullptr) { Node* t = head; head = head->next; delete t; }
    tail = nullptr; sz = 0;
    
    size_t file_sz = 0;
    if (!f.read(reinterpret_cast<char*>(&file_sz), sizeof(file_sz))) return;
    if (file_sz > 1000000) return;
    
    for (size_t i = 0; i < file_sz; ++i) {
        size_t len = 0;
        if (!f.read(reinterpret_cast<char*>(&len), sizeof(len))) break;
        if (len > 1000000) break;
        
        std::string temp(len, '\0');
        if (!f.read(&temp[0], len)) break;
        push_back(temp);
    }
}