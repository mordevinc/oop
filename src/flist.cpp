#include "flist.h"
#include <fstream>

// Конструктор. Список пуст: голова и хвост смотрят в никуда (nullptr).
ForwardList::ForwardList() : head(nullptr), tail(nullptr), sz(0) {}

// Конструктор копирования (правило трех)
ForwardList::ForwardList(const ForwardList& other) : head(nullptr), tail(nullptr), sz(0) {
    Node* curr = other.head;
    while (curr != nullptr) {
        push_back(curr->data); // Поэлементно копируем в новый список
        curr = curr->next;
    }
}

// Оператор присваивания (правило трех)
ForwardList& ForwardList::operator=(const ForwardList& other) {
    if (this != &other) {
        // Очищаем текущий список
        while (head != nullptr) {
            Node* t = head; head = head->next; delete t;
        }
        tail = nullptr; sz = 0;
        
        // Копируем элементы из другого списка
        Node* curr = other.head;
        while (curr != nullptr) {
            push_back(curr->data);
            curr = curr->next;
        }
    }
    return *this;
}

// Деструктор. Идем от головы к хвосту и удаляем каждый узел.
ForwardList::~ForwardList() {
    Node* curr = head;
    while (curr != nullptr) {
        Node* temp = curr; // Запоминаем текущий узел
        curr = curr->next; // Переходим к следующему
        delete temp;       // Удаляем запомненный (освобождаем память)
    }
}

// Добавление элемента в конец списка.
void ForwardList::push_back(const std::string& value) {
    Node* newNode = new Node(value); // Создаем новый узел в куче
    
    if (tail == nullptr) { // Если список был пуст
        head = newNode;
        tail = newNode;
    } else { // Если элементы уже есть
        tail->next = newNode; // Старый хвост теперь ссылается на новый узел
        tail = newNode;       // Новый узел официально становится хвостом
    }
    sz++;
}

// Добавление элемента в начало списка.
void ForwardList::push_front(const std::string& value) {
    Node* newNode = new Node(value);
    newNode->next = head; // Новый узел ссылается на старую голову
    head = newNode;       // Новый узел становится головой
    
    if (tail == nullptr) { // Если список был пуст, то это и хвост тоже
        tail = newNode;
    }
    sz++;
}

// Поиск элемента по значению.
bool ForwardList::find(const std::string& value) const {
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data == value) return true; // Нашли совпадение
        curr = curr->next; // Идем дальше
    }
    return false; // Прошли весь список, не нашли
}

// Возврат размера.
size_t ForwardList::size() const { 
    return sz; 
}

// Печать списка.
void ForwardList::print() const {
    Node* curr = head;
    std::cout << "List: ";
    while (curr != nullptr) {
        std::cout << curr->data << " -> ";
        curr = curr->next;
    }
    std::cout << "nullptr\n";
}

// Сохранение в файл.
void ForwardList::save(const std::string& filename) const {
    std::ofstream f(filename, std::ios::binary);
    f.write(reinterpret_cast<const char*>(&sz), sizeof(sz)); // Пишем размер списка
    
    Node* curr = head;
    while (curr != nullptr) {
        size_t len = curr->data.size();
        f.write(reinterpret_cast<const char*>(&len), sizeof(len)); // Пишем длину строки
        f.write(curr->data.c_str(), len);                          // Пишем саму строку
        curr = curr->next;
    }
}

// Загрузка из файла.
void ForwardList::load(const std::string& filename) {
    std::ifstream f(filename, std::ios::binary);
    if (!f) return;
    
    // Очищаем текущий список
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
        size_t len = 0; // Инициализация!
        if (!f.read(reinterpret_cast<char*>(&len), sizeof(len))) break;
        
        std::string temp(len, '\0');
        if (!f.read(&temp[0], len)) break;
        
        push_back(temp);
    }
}