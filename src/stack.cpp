#include "stack.h"
#include <fstream>

// Инициализация пустого стека.
// Параметр cap оставлен для совместимости с заданием, но в данной реализации не используется.
Stack::Stack(size_t cap) : head(nullptr), sz(0) {
    (void)cap; // Явно указываем компилятору, что параметр не используется, чтобы не было warning
}

// Деструктор.
Stack::~Stack() {
    while (head != nullptr) { 
        Node* t = head; 
        head = head->next; 
        delete t; 
    }
}

// Кладем элемент на вершину (в начало списка).
void Stack::push(const std::string& value) {
    Node* newNode = new Node(value);
    newNode->next = head; // Новый узел указывает на старую вершину
    head = newNode;       // Новый узел становится вершиной
    sz++;
}

// Снимаем элемент с вершины.
std::string Stack::pop() {
    if (head == nullptr) return ""; // Если стек пуст, возвращаем пустоту
    
    Node* temp = head;
    std::string val = temp->data; // Запоминаем данные
    head = head->next;            // Сдвигаем вершину на следующий узел
    delete temp;                  // Удаляем старую вершину
    sz--;
    return val;
}

// Проверка на пустоту.
bool Stack::empty() const { 
    return head == nullptr; 
}

// Размер.
size_t Stack::size() const { 
    return sz; 
}

// Печать стека (сверху вниз).
void Stack::print() const {
    Node* curr = head;
    std::cout << "Stack (top -> bottom): ";
    while (curr != nullptr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << "\n";
}

// Сохранение. Сохраняем элементы в порядке от вершины к основанию.
void Stack::save(const std::string& filename) const {
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

// Загрузка. При загрузке используем временный массив, чтобы сохранить порядок.
void Stack::load(const std::string& filename) {
    std::ifstream f(filename, std::ios::binary);
    if (!f) return;
    
    while (head != nullptr) { Node* t = head; head = head->next; delete t; }
    sz = 0;
    
    size_t file_sz = 0;
    if (!f.read(reinterpret_cast<char*>(&file_sz), sizeof(file_sz))) return;
    if (file_sz > 1000000) return; // Защита от мусора
    
    // Временный массив для сохранения правильного порядка
    std::string* temp_arr = new std::string[file_sz];
    size_t count = 0;
    
    for (size_t i = 0; i < file_sz; ++i) {
        size_t len = 0;
        if (!f.read(reinterpret_cast<char*>(&len), sizeof(len))) break;
        if (len > 1000000) break;
        
        std::string temp(len, '\0');
        if (!f.read(&temp[0], len)) break;
        temp_arr[count++] = temp;
    }
    
    // Восстанавливаем стек с конца массива, чтобы "Top" снова стал вершиной
    for (int i = (int)count - 1; i >= 0; --i) {
        push(temp_arr[i]);
    }
    delete[] temp_arr;
}